// -*- Mode: C++; indent-tabs-mode: nil; c-basic-offset: 4; fill-column: 78 -*-
//
// OpenVRML
//
// Copyright 1998  Chris Morley
// Copyright 2001, 2002, 2003, 2004, 2005, 2006, 2007, 2009  Braden McDaniel
// Copyright 2002  S. K. Bose
//
// This library is free software; you can redistribute it and/or modify it
// under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation; either version 3 of the License, or (at your
// option) any later version.
//
// This library is distributed in the hope that it will be useful, but WITHOUT
// ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
// FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public
// License for more details.
//
// You should have received a copy of the GNU Lesser General Public License
// along with this library; if not, see <http://www.gnu.org/licenses/>.
//

# include "audio_clip.h"
# include <openvrml/browser.h>
# include <openvrml/node_impl_util.h>
# include <openvrml/scene.h>
# include <boost/array.hpp>

# ifdef HAVE_CONFIG_H
#   include <config.h>
# endif

namespace {

    class OPENVRML_LOCAL audio_clip_node :
        public openvrml::node_impl_util::abstract_node<audio_clip_node>,
        public openvrml::time_dependent_node {

        friend class openvrml_node_vrml97::audio_clip_metatype;

        exposedfield<openvrml::sfstring> description_;
        exposedfield<openvrml::sfbool> loop_;
        exposedfield<openvrml::sffloat> pitch_;
        exposedfield<openvrml::sftime> start_time_;
        exposedfield<openvrml::sftime> stop_time_;
        exposedfield<openvrml::mfstring> url_;
        exposedfield<openvrml::sftime> pause_time_;
        exposedfield<openvrml::sftime> resume_time_;
        openvrml::sftime duration_changed_;
        sftime_emitter duration_changed_emitter_;
        openvrml::sfbool is_active_;
        sfbool_emitter is_active_emitter_;
        openvrml::sftime elapsed_time_;
        sftime_emitter elapsed_time_emitter_;
        openvrml::sfbool is_paused_;
        sfbool_emitter is_paused_emitter_;


    public:
        audio_clip_node(const openvrml::node_type & type,
                        const boost::shared_ptr<openvrml::scope> & scope);
        virtual ~audio_clip_node() OPENVRML_NOTHROW;

    private:
        virtual void do_initialize(double timestamp) OPENVRML_THROW1(std::bad_alloc);
        virtual void do_shutdown(double timestamp) OPENVRML_NOTHROW;
        virtual void do_update(double time);
    };


    /**
     * @class audio_clip_node
     *
     * @brief AudioClip node instances.
     *
     * @todo Implement sound support.
     */

    /**
     * @var class audio_clip_node::audio_clip_metatype
     *
     * @brief Class object for AudioClip nodes.
     */

    /**
     * @var openvrml::node_impl_util::abstract_node<audio_clip_node>::exposedfield<openvrml::sfstring> audio_clip_node::description_
     *
     * @brief description exposedField.
     */

    /**
     * @var openvrml::node_impl_util::abstract_node<audio_clip_node>::exposedfield<openvrml::sfbool> audio_clip_node::loop_
     *
     * @brief loop exposedField.
     */

    /**
     * @var openvrml::node_impl_util::abstract_node<audio_clip_node>::exposedfield<openvrml::sffloat> audio_clip_node::pitch_
     *
     * @brief pitch exposedField.
     */

    /**
     * @var openvrml::node_impl_util::abstract_node<audio_clip_node>::exposedfield<openvrml::sftime> audio_clip_node::start_time_
     *
     * @brief startTime exposedField.
     */

    /**
     * @var openvrml::node_impl_util::abstract_node<audio_clip_node>::exposedfield<openvrml::sftime> audio_clip_node::stop_time_
     *
     * @brief stopTime exposedField.
     */

    /**
     * @var openvrml::node_impl_util::abstract_node<audio_clip_node>::exposedfield<openvrml::mfstring> audio_clip_node::url_
     *
     * @brief url exposedField.
     */

    /**
     * @var openvrml::sftime audio_clip_node::duration_changed_
     *
     * @brief duration_changed eventOut value.
     */

    /**
     * @var openvrml::sftime_emitter audio_clip_node::duration_changed_emitter_
     *
     * @brief duration_changed eventOut emitter.
     */

    /**
     * @var openvrml::sfbool audio_clip_node::is_active_
     *
     * @brief isActive eventOut value.
     */

    /**
     * @var openvrml::sfbool_emitter audio_clip_node::is_active_emitter_
     *
     * @brief isActive eventOut emitter.
     */

    /**
     * @brief Construct.
     *
     * @param type      the node_type associated with the node instance.
     * @param scope     the scope to which the node belongs.
     */
    audio_clip_node::
    audio_clip_node(const openvrml::node_type & type,
                    const boost::shared_ptr<openvrml::scope> & scope):
        node(type, scope),
        openvrml::node_impl_util::abstract_node<audio_clip_node>(type, scope),
        time_dependent_node(type, scope),
        description_(*this),
        loop_(*this),
        pitch_(*this, 1.0),
        start_time_(*this),
        stop_time_(*this),
        url_(*this),
        pause_time_(*this),
        resume_time_(*this),
        duration_changed_emitter_(*this, this->duration_changed_),
        is_active_emitter_(*this, this->is_active_),
        elapsed_time_emitter_(*this, this->elapsed_time_),
        is_paused_emitter_(*this, this->is_paused_)
    {}

    /**
     * @brief Destroy.
     */
    audio_clip_node::~audio_clip_node() OPENVRML_NOTHROW
    {}

    /**
     * @brief Called to update the AudioClip for the current time.
     *
     * @param time  the current time.
     *
     * @todo Implement me!
     */
    void audio_clip_node::do_update(double)
    {}

    /**
     * @brief Initialize.
     *
     * @param timestamp the current time.
     *
     * @exception std::bad_alloc    if memory allocation fails.
     */
    void
    audio_clip_node::do_initialize(double)
        OPENVRML_THROW1(std::bad_alloc)
    {
        assert(this->scene());
        this->scene()->browser().add_time_dependent(*this);
    }

    /**
     * @brief Shut down.
     *
     * @param timestamp the current time.
     */
    void
    audio_clip_node::do_shutdown(double) OPENVRML_NOTHROW
    {
        assert(this->scene());
        this->scene()->browser().remove_time_dependent(*this);
    }
}


/**
 * @brief @c node_metatype identifier.
 */
const char * const openvrml_node_vrml97::audio_clip_metatype::id =
    "urn:X-openvrml:node:AudioClip";

/**
 * @brief Construct.
 *
 * @param browser the @c browser associated with this class object.
 */
openvrml_node_vrml97::audio_clip_metatype::
audio_clip_metatype(openvrml::browser & browser):
    node_metatype(audio_clip_metatype::id, browser)
{}

/**
 * @brief Destroy.
 */
openvrml_node_vrml97::audio_clip_metatype::~audio_clip_metatype()
    OPENVRML_NOTHROW
{}

# define AUDIO_CLIP_INTERFACE_SEQ \
    ((exposedfield, sfstring, "description",      description_))        \
    ((exposedfield, sfbool,   "loop",             loop_))               \
    ((exposedfield, sffloat,  "pitch",            pitch_))              \
    ((exposedfield, sftime,   "startTime",        start_time_))         \
    ((exposedfield, sftime,   "stopTime",         stop_time_))          \
    ((exposedfield, mfstring, "url",              url_))                \
    ((eventout,     sftime,   "duration_changed", duration_changed_emitter_)) \
    ((eventout,     sfbool,   "isActive",         is_active_emitter_))  \
    ((exposedfield, sfnode,   "metadata",         metadata))            \
    ((exposedfield, sftime,   "pauseTime",        pause_time_))         \
    ((exposedfield, sftime,   "resumeTime",       resume_time_))        \
    ((eventout,     sftime,   "elapsedTime",      elapsed_time_emitter_)) \
    ((eventout,     sfbool,   "isPaused",         is_paused_emitter_))

OPENVRML_NODE_IMPL_UTIL_DEFINE_DO_CREATE_TYPE(openvrml_node_vrml97,
                                              audio_clip_metatype,
                                              audio_clip_node,
                                              AUDIO_CLIP_INTERFACE_SEQ)
