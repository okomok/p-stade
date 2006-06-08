#ifndef PSTADE_LIME_FIND_HPP
#define PSTADE_LIME_FIND_HPP


// PStade.Lime
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/foreach.hpp>
#include <boost/implicit_cast.hpp>
#include <boost/optional.hpp>
#include "./node_value_type.hpp"


namespace pstade { namespace lime {


template< class Node >
typename node_value<Node>::type&
find_root(Node& child)
{
    typedef typename node_value<Node>::type parent_t;

    boost::optional<parent_t&> parent = child.parent();

    if (!parent)
        return child;
    else
        return lime::find_root(parent);
}


template< class Node, class UnaryPred >
boost::optional<typename node_value<Node>::type&>
find_up(Node& node, UnaryPred pred)
{
    typedef typename node_value<Node>::type val_t;
    typedef boost::optional<val_t&> opt_t;

    if (pred(node))
        return opt_t(boost::implicit_cast<val_t&>(node));

    opt_t pa = node.parent();
    if (!pa)
        return opt_t();

    return lime::find_up(*pa, pred);
}


template< class Node, class UnaryPred >
typename node_value<Node>::type&
find_child(Node& parent, UnaryPred pred)
{
    typedef typename node_value<Node>::type child_t;
    typedef boost::optional<child_t&> opt_t;

    BOOST_FOREACH (child_t& child, parent) {
        if (pred(child))
            return opt_t(child);
    }

    return opt_t();
}


} } // namespace pstade::lime


#endif
