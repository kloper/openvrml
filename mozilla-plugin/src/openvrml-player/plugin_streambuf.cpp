// -*- Mode: C++; indent-tabs-mode: nil; c-basic-offset: 4; fill-column: 78 -*-
//
// OpenVRML Mozilla plug-in
// Copyright 2004, 2005, 2006  Braden N. McDaniel
//
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
//

# include <glib.h>
# include "plugin_streambuf.h"

openvrml_player::plugin_streambuf::npstream_buffer::npstream_buffer():
    begin_(0),
    end_(0),
    buffered_(0),
    npstream_destroyed_(false)
{}

void
openvrml_player::plugin_streambuf::npstream_buffer::put(const char_type & c)
{
    boost::mutex::scoped_lock lock(this->mutex_);
    while (this->buffered_ == npstream_buffer::buffer_size) {
        this->buffer_not_full_.wait(lock);
    }
    this->buf_[this->end_] = c;
    this->end_ = (this->end_ + 1) % npstream_buffer::buffer_size;
    ++this->buffered_;
    this->buffer_not_empty_or_eof_.notify_one();
}

openvrml_player::plugin_streambuf::int_type
openvrml_player::plugin_streambuf::npstream_buffer::get()
{
    boost::mutex::scoped_lock lock(this->mutex_);
    while (this->buffered_ == 0 && !this->npstream_destroyed_) {
        this->buffer_not_empty_or_eof_.wait(lock);
    }
    if (this->buffered_ == 0 && this->npstream_destroyed_) {
        return traits_type::eof();
    }
    const char_type c = this->buf_[this->begin_];
    this->begin_ = (this->begin_ + 1) % npstream_buffer::buffer_size;
    --this->buffered_;
    this->buffer_not_full_.notify_one();
    const int_type i = traits_type::to_int_type(c);
    assert(!traits_type::eq_int_type(i, traits_type::eof()));
    return i;
}

size_t openvrml_player::plugin_streambuf::npstream_buffer::buffered() const
{
    boost::mutex::scoped_lock lock(this->mutex_);
    return this->buffered_;
}

void openvrml_player::plugin_streambuf::npstream_buffer::npstream_destroyed()
{
    boost::mutex::scoped_lock lock(this->mutex_);
    this->npstream_destroyed_ = true;
    this->buffer_not_empty_or_eof_.notify_one();
}

openvrml_player::plugin_streambuf::
plugin_streambuf(const std::string & requested_url):
    initialized_(false),
    url_(requested_url),
    i_(0),
    c_('\0')
{
    //
    // This is really just here to emphasize that c_ must not be EOF.
    //
    this->i_ = traits_type::not_eof(this->i_);
    this->c_ =
        traits_type::to_char_type(
            traits_type::not_eof(traits_type::to_int_type(this->c_)));

    this->setg(&this->c_, &this->c_, &this->c_);
}

void openvrml_player::plugin_streambuf::init(const size_t stream_id,
                                             const std::string & received_url,
                                             const std::string & type)
{
    boost::mutex::scoped_lock lock(this->mutex_);
    bool succeeded = uninitialized_plugin_streambuf_map_.erase(this->url_);
    g_assert(succeeded);
    this->url_ = received_url;
    this->type_ = type;
    this->initialized_ = true;
    const boost::shared_ptr<plugin_streambuf> this_ = shared_from_this();
    succeeded = plugin_streambuf_map.insert(make_pair(stream_id, this_))
        .second;
    g_assert(succeeded);
    this->streambuf_initialized_.notify_all();
}

const std::string & openvrml_player::plugin_streambuf::url() const
{
    boost::mutex::scoped_lock lock(this->mutex_);
    while (!this->initialized_) {
        this->streambuf_initialized_.wait(lock);
    }
    return this->url_;
}

const std::string & openvrml_player::plugin_streambuf::type() const
{
    boost::mutex::scoped_lock lock(this->mutex_);
    while (!this->initialized_) {
        this->streambuf_initialized_.wait(lock);
    }
    return this->type_;
}

bool openvrml_player::plugin_streambuf::data_available() const
{
    return this->buf_.buffered() > 0;
}

openvrml_player::plugin_streambuf::int_type
openvrml_player::plugin_streambuf::underflow()
{
    boost::mutex::scoped_lock lock(this->mutex_);
    while (!this->initialized_) {
        this->streambuf_initialized_.wait(lock);
    }
    if (this->c_ == traits_type::eof()) { return traits_type::eof(); }
    this->c_ = this->buf_.get();
    this->setg(&this->c_, &this->c_, &this->c_ + 1);
    return *this->gptr();
}


openvrml_player::uninitialized_plugin_streambuf_map
openvrml_player::uninitialized_plugin_streambuf_map_;

const boost::shared_ptr<openvrml_player::plugin_streambuf>
openvrml_player::uninitialized_plugin_streambuf_map::
find(const std::string & url) const
{
    boost::mutex::scoped_lock lock(this->mutex_);
    map_t::const_iterator pos = this->map_.find(url);
    return pos == this->map_.end()
        ? boost::shared_ptr<plugin_streambuf>()
        : pos->second;
}

bool
openvrml_player::uninitialized_plugin_streambuf_map::
insert(const std::string & url,
       const boost::shared_ptr<openvrml_player::plugin_streambuf> & streambuf)
{
    boost::mutex::scoped_lock lock(this->mutex_);
    return this->map_.insert(make_pair(url, streambuf)).second;
}

bool
openvrml_player::uninitialized_plugin_streambuf_map::
erase(const std::string & url)
{
    boost::mutex::scoped_lock lock(this->mutex_);
    return this->map_.erase(url) == 1;
}

size_t openvrml_player::uninitialized_plugin_streambuf_map::size() const
{
    boost::mutex::scoped_lock lock(this->mutex_);
    return this->map_.size();
}

const boost::shared_ptr<openvrml_player::plugin_streambuf>
openvrml_player::uninitialized_plugin_streambuf_map::front() const
{
    boost::mutex::scoped_lock lock(this->mutex_);
    g_assert(!this->map_.empty());
    return this->map_.begin()->second;
}


openvrml_player::plugin_streambuf_map_t openvrml_player::plugin_streambuf_map;
