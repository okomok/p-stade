#ifndef PSTADE_LIME_NEW_NODE_HPP
#define PSTADE_LIME_NEW_NODE_HPP


// PStade.Lime
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/overload.hpp>
#include <pstade/ustring.hpp>
#include "./node_value.hpp"


namespace pstade { namespace lime {


namespace new_node_detail {


    template< class Node > inline
    typename node_value<Node>::type *
    pstade_lime_new_node(Node& parent, ustring childName)
    {
         return pstade_lime_new_node(parent, childName, overload<>());
    }


} // namespace new_node_detail


template< class Node > inline
typename node_value<Node>::type *
new_node(Node& parent, ustring childName)
{
    using namespace new_node_detail;
    return pstade_lime_new_node(parent, childName);
}


} } // namespace pstade::lime


// default
//
template< class Node > inline
Node *pstade_lime_new_node(Node& parent, pstade::ustring childName, pstade::overload<>)
{
    return new Node(parent, childName);
}


#endif
