// -*- Mode: C++; indent-tabs-mode: nil; c-basic-offset: 4; -*-
//
// OpenVRML
//
// Copyright (C) 1998  Chris Morley
// Copyright (C) 2002  Braden McDaniel
//
// This library is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public
// License as published by the Free Software Foundation; either
// version 2.1 of the License, or (at your option) any later version.
//
// This library is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
// Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public
// License along with this library; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
//

# ifdef HAVE_CONFIG_H
#   include <config.h>
# endif

# include <algorithm>
# include "scope.h"
# include "node.h"

namespace OpenVRML {

/**
 * @class scope
 *
 * @brief The scope class keeps track of defined nodes and
 *      prototypes.
 *
 * PROTO definitions add node types to the namespace.
 * PROTO implementations are a separate node type namespace,
 * and require that any nested PROTOs NOT be available outside
 * the PROTO implementation. PROTOs defined outside the current
 * namespace are available.
 */

typedef std::list<node_type_ptr> node_type_list_t;

/**
 * @brief Construct.
 *
 * @param id        the identifier for the scope.
 * @param parent    the parent scope.
 */
scope::scope(const std::string & id, const ScopePtr & parent):
    id(id),
    parent(parent)
{}

/**
 * @brief Destroy.
 */
scope::~scope()
{}

/**
 * @brief Add a node type.
 *
 * Print an error message if the argument type is already defined.
 *
 * @param nodeType a node_type_ptr
 *
 * @todo Throw std::invalid_argument if the argument type is already defined.
 */
void scope::add_type(const node_type_ptr & type)
{
    assert(type);
    assert(!this->find_type(type->id));
    this->node_type_list.push_front(type);
}

namespace {
    struct has_id_ : std::unary_function<node_type_ptr, bool> {
        has_id_(const std::string & id):
            id(&id)
        {}

        bool operator()(const node_type_ptr & type) const
        {
            assert(type);
            return type->id == *this->id;
        }

    private:
        const std::string * id;
    };
}

/**
 * @brief Find a node type, given a type name. Returns 0 if type is
 *      not defined.
 */
const node_type_ptr scope::find_type(const std::string & id) const {
    //
    // Look through the types unique to this scope.
    //
    const node_type_list_t::const_iterator end = this->node_type_list.end();
    const node_type_list_t::const_iterator pos =
            std::find_if(this->node_type_list.begin(), end, has_id_(id));
    if (pos != end) { return *pos; }

    //
    // Look in the parent scope for the type.
    //
    return this->parent
            ? this->parent->find_type(id)
            : node_type_ptr(0);
}

const node_type_ptr scope::first_type() const
{
    return !this->node_type_list.empty()
            ? this->node_type_list.front()
            : node_type_ptr(0);
}

typedef std::map<std::string, node *> named_node_map_t;

node * scope::find_node(const std::string & id) const
{
    const named_node_map_t::const_iterator pos = this->named_node_map.find(id);
    return (pos != this->named_node_map.end())
            ? pos->second
            : 0;
}

} // namespace OpenVRML

