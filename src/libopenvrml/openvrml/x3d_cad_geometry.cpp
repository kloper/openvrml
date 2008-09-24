// -*- mode: c++; indent-tabs-mode: nil; c-basic-offset: 4; fill-column: 78 -*-
//
// OpenVRML
//
// Copyright 2006, 2007, 2008  Braden McDaniel
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

# include "browser.h"
# include "x3d_cad_geometry.h"
# include <x3d-cad-geometry/cad_face.h>
# include <x3d-cad-geometry/indexed_quad_set.h>

# ifdef HAVE_CONFIG_H
#   include <config.h>
# endif

void register_cad_geometry_node_metatypes(openvrml::browser & b)
{
    using openvrml::node_metatype;
    using boost::shared_ptr;
    using namespace openvrml_node_x3d_cad_geometry;
    b.add_node_metatype(cad_face_metatype::id,
                        shared_ptr<node_metatype>(new cad_face_metatype(b)));
    b.add_node_metatype(indexed_quad_set_metatype::id,
                        shared_ptr<node_metatype>(
                            new indexed_quad_set_metatype(b)));
}
