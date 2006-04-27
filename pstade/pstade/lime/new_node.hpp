#ifndef PSTADE_LIME_NEW_NODE_HPP
#define PSTADE_LIME_NEW_NODE_HPP


// PStade.Lime
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/overload.hpp>
#include "./node.hpp"
#include "./ustring.hpp"


namespace pstade { namespace lime {


template< class Interface > inline
node<Interface> *
new_node(ustring name, node<Interface>& parent)
{
    return pstade_lemon_new_node(name, parent, overload());
}


// default
//
inline
node<pstade::lime::default_interface> *
pstade_lemon_new_node(ustring name, node<pstade::lime::default_interface>& parent, pstade::overload)
{
	using namespace pstade::lime;
    return new node<default_interface>(name, parent);
}


} } // namespace pstade::lime


#endif
