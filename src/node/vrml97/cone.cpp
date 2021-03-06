// -*- Mode: C++; indent-tabs-mode: nil; c-basic-offset: 4; fill-column: 78 -*-
//
// OpenVRML
//
// Copyright 1998  Chris Morley
// Copyright 2001, 2002, 2003, 2004, 2005, 2006, 2007, 2009  Braden McDaniel
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

# include "cone.h"
# include <openvrml/node_impl_util.h>
# include <openvrml/viewer.h>
# include <boost/array.hpp>

# ifdef HAVE_CONFIG_H
#   include <config.h>
# endif

namespace {

    class OPENVRML_LOCAL cone_node :
        public openvrml::node_impl_util::abstract_node<cone_node>,
        public openvrml::geometry_node {

        friend class openvrml_node_vrml97::cone_metatype;

        openvrml::sfbool bottom;
        openvrml::sffloat bottomRadius;
        openvrml::sffloat height;
        openvrml::sfbool side;
        openvrml::sfbool solid_;

        openvrml::bounding_sphere bsphere;

    public:
        cone_node(const openvrml::node_type & type,
                  const boost::shared_ptr<openvrml::scope> & scope);
        virtual ~cone_node() OPENVRML_NOTHROW;

    private:
        virtual const openvrml::bounding_volume & do_bounding_volume() const;
        virtual void do_render_geometry(openvrml::viewer & viewer,
                                        openvrml::rendering_context context);
    };

    /**
     * @class cone_node
     *
     * @brief Cone node instances.
     */

    /**
     * @var class cone_node::cone_metatype
     *
     * @brief Class object for Cone nodes.
     */

    /**
     * @var openvrml::sfbool cone_node::bottom
     *
     * @brief bottom field.
     */

    /**
     * @var openvrml::sffloat cone_node::bottomRadius
     *
     * @brief bottomRadius field.
     */

    /**
     * @var openvrml::sffloat cone_node::height
     *
     * @brief height field.
     */

    /**
     * @var openvrml::sfbool cone_node::side
     *
     * @brief side field.
     */

    /**
     * @brief Construct.
     *
     * @param type  the node_type associated with the node instance.
     * @param scope     the scope to which the node belongs.
     */
    cone_node::
    cone_node(const openvrml::node_type & type,
              const boost::shared_ptr<openvrml::scope> & scope):
        node(type, scope),
        bounded_volume_node(type, scope),
        openvrml::node_impl_util::abstract_node<cone_node>(type, scope),
        geometry_node(type, scope),
        bottom(true),
        bottomRadius(1.0),
        height(2.0),
        side(true),
        solid_(true)
    {
        this->bounding_volume_dirty(true); // lazy calc of bvolume
    }

    /**
     * @brief Destroy.
     */
    cone_node::~cone_node() OPENVRML_NOTHROW
    {}

    /**
     * @brief Insert this geometry into @p viewer's display list.
     *
     * @param viewer    a viewer.
     * @param context   the rendering context.
     */
    void cone_node::do_render_geometry(openvrml::viewer & viewer,
                                       openvrml::rendering_context)
    {
        viewer.insert_cone(*this,
                           this->height.value(),
                           this->bottomRadius.value(),
                           this->bottom.value(),
                           this->side.value());
    }

    /**
     * @brief Get the bounding volume.
     *
     * @return the bounding volume associated with the node.
     */
    const openvrml::bounding_volume &
    cone_node::do_bounding_volume() const
    {
        if (this->bounding_volume_dirty()) {
            float h = height.value();
            float r = bottomRadius.value();
            float bounding_radius;
            openvrml::vec3f bounding_center;
            
            if( h > r ) {
                bounding_radius = (h*h + r*r) / (2.0*h);
                bounding_center = 
                    openvrml::make_vec3f(0, h/2.0 - bounding_radius, 0);
            } else {
                bounding_radius = r;
                bounding_center = openvrml::make_vec3f(0,0,0);
            }
            const_cast<cone_node *>(this)->bsphere.radius(bounding_radius);
            const_cast<cone_node *>(this)->bsphere.center(bounding_center);
            const_cast<cone_node *>(this)->bounding_volume_dirty(false); 
        }
        return this->bsphere;
    }

}


/**
 * @brief @c node_metatype identifier.
 */
const char * const openvrml_node_vrml97::cone_metatype::id =
    "urn:X-openvrml:node:Cone";

/**
 * @brief Construct.
 *
 * @param browser the @c browser associated with this class object.
 */
openvrml_node_vrml97::cone_metatype::
cone_metatype(openvrml::browser & browser):
    node_metatype(cone_metatype::id, browser)
{}

/**
 * @brief Destroy.
 */
openvrml_node_vrml97::cone_metatype::~cone_metatype() OPENVRML_NOTHROW
{}

# define CONE_INTERFACE_SEQ                                  \
    ((field,        sffloat, "bottomRadius", bottomRadius))  \
    ((field,        sffloat, "height",       height))        \
    ((field,        sfbool,  "side",         side))          \
    ((field,        sfbool,  "bottom",       bottom))        \
    ((exposedfield, sfnode,  "metadata",     metadata))      \
    ((field,        sfbool,  "solid",        solid_))

OPENVRML_NODE_IMPL_UTIL_DEFINE_DO_CREATE_TYPE(openvrml_node_vrml97,
                                              cone_metatype,
                                              cone_node,
                                              CONE_INTERFACE_SEQ)
