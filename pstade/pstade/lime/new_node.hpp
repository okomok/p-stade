#ifndef PSTADE_LIME_NEW_NODE_HPP
#define PSTADE_LIME_NEW_NODE_HPP


// PStade.Lime
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/oven/range_pointer.hpp>
#include <pstade/ustring.hpp>
#include "./extension.hpp"


namespace pstade_lime_extension {


    // default
    template< class Node > inline
    Node *pstade_lime_(new_node, Node& parent, pstade::ustring const& childName)
    {
        return new Node(parent, childName);
    }


} // namespace pstade_lime_extension


namespace pstade { namespace lime {


    template< class Node > inline
    typename oven::range_pointer<Node>::type
    pstade_lime_new_node(Node& parent, ustring const& childName)
    {
         return pstade_lime_(pstade_lime_extension::new_node(), parent, childName);
    }


    template< class Node > inline
    typename oven::range_pointer<Node>::type
    new_node(Node& parent, ustring const& childName)
    {
        return pstade_lime_new_node(parent, childName);
    }


} } // namespace pstade::lime


#endif
