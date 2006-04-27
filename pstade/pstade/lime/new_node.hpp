#ifndef PSTADE_LIME_NEW_NODE_HPP
#define PSTADE_LIME_NEW_NODE_HPP


// PStade.Lime
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/mpl/empty_base.hpp>
#include "./node.hpp"
#include "./ustring.hpp"


namespace pstade { namespace lime {


namespace new_node_detail {


    inline
    node<default_interface> *
	pstade_lemon_new_node(ustring name, node<default_interface>& parent, default_interface)
    {
        return new node<default_interface>(name, parent);
    }


} // namespace new_node_detail


template< class Interface > inline
node<Interface> *
new_node(ustring name, node<Interface>& parent)
{
    using namespace new_node_detail;

    return pstade_lemon_new_node(name, parent, Interface());
}


} } // namespace pstade::lime


#endif
