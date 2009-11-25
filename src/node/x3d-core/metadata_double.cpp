// -*- mode: c++; indent-tabs-mode: nil; c-basic-offset: 4; fill-column: 78 -*-
//
// OpenVRML
//
// Copyright 2006, 2007, 2008, 2009  Braden McDaniel
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

# include "metadata_double.h"
# include <openvrml/node_impl_util.h>
# include <boost/array.hpp>

# ifdef HAVE_CONFIG_H
#   include <config.h>
# endif

using namespace openvrml;
using namespace openvrml::node_impl_util;
using namespace std;


namespace {

    /**
     * @brief Represents MetadataDouble node instances.
     */
    class OPENVRML_LOCAL metadata_double_node :
        public abstract_node<metadata_double_node> {

        friend class openvrml_node_x3d_core::metadata_double_metatype;

        exposedfield<sfstring> name_;
        exposedfield<sfstring> reference_;
        exposedfield<mfdouble> value_;

    public:
        metadata_double_node(const node_type & type, 
                             const boost::shared_ptr<openvrml::scope> & scope);
        virtual ~metadata_double_node() OPENVRML_NOTHROW;
    };


    /**
     * @var metadata_double_node::metadata_double_metatype
     *
     * @brief Class object for MetadataDouble nodes.
     */

    /**
     * @var metadata_double_node::name_
     *
     * @brief name exposedField
     */

    /**
     * @var metadata_double_node::reference_
     *
     * @brief reference exposedField
     */

    /**
     * @var metadata_double_node::value_
     *
     * @brief value exposedField
     */

    
    /**
     * @brief Construct.
     *
     * @param type  the node_type associated with this node.
     * @param scope     the scope to which the node belongs.
     */
    metadata_double_node::
    metadata_double_node(const node_type & type,
                         const boost::shared_ptr<openvrml::scope> & scope):
        node(type, scope),
        abstract_node<self_t>(type, scope),
        name_(*this),
        reference_(*this),
        value_(*this)
    {}

    /**
     * @brief Destroy.
     */
    metadata_double_node::~metadata_double_node() OPENVRML_NOTHROW
    {}
}


/**
 * @brief @c node_metatype identifier.
 */
const char * const openvrml_node_x3d_core::metadata_double_metatype::id =
    "urn:X-openvrml:node:MetadataDouble";

/**
 * @brief Construct.
 *
 * @param browser the @c browser associated with this
 *                @c metadata_double_metatype.
 */
openvrml_node_x3d_core::metadata_double_metatype::
metadata_double_metatype(openvrml::browser & browser):
    node_metatype(metadata_double_metatype::id, browser)
{}

/**
 * @brief Destroy.
 */
openvrml_node_x3d_core::metadata_double_metatype::~metadata_double_metatype()
    OPENVRML_NOTHROW
{}

# define METADATA_DOUBLE_INTERFACE_SEQ                  \
    ((exposedfield, sfnode,   "metadata",  metadata))   \
    ((exposedfield, sfstring, "name",      name_))      \
    ((exposedfield, sfstring, "reference", reference_)) \
    ((exposedfield, mfdouble, "value",     value_))

OPENVRML_NODE_IMPL_UTIL_DEFINE_DO_CREATE_TYPE(openvrml_node_x3d_core,
                                              metadata_double_metatype,
                                              metadata_double_node,
                                              METADATA_DOUBLE_INTERFACE_SEQ)
