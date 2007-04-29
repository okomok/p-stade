#ifndef PSTADE_LIME_FIND_HPP
#define PSTADE_LIME_FIND_HPP


// PStade.Lime
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/foreach.hpp>
#include <boost/implicit_cast.hpp>
#include <boost/optional/optional.hpp>
#include <pstade/oven/range_reference.hpp>


namespace pstade { namespace lime {


    template< class Node >
    typename oven::range_reference<Node>::type
    find_root(Node& child)
    {
        typedef typename oven::range_reference<Node>::type parent_t;

        boost::optional<parent_t> parent = child.parent();

        if (!parent)
            return child;
        else
            return lime::find_root(parent);
    }


    template< class Node, class UnaryPred >
    boost::optional<typename oven::range_reference<Node>::type>
    find_up(Node& node, UnaryPred pred)
    {
        typedef typename oven::range_reference<Node>::type ref_t;
        typedef boost::optional<ref_t> opt_t;

        if (pred(node))
            return opt_t(boost::implicit_cast<ref_t>(node));

        opt_t pa = node.parent();
        if (!pa)
            return opt_t();

        return lime::find_up(*pa, pred);
    }


    template< class Node, class UnaryPred >
    typename oven::range_reference<Node>::type
    find_child(Node& parent, UnaryPred pred)
    {
        typedef typename oven::range_reference<Node>::type child_t;
        typedef boost::optional<child_t> opt_t;

        BOOST_FOREACH (child_t child, parent) {
            if (pred(child))
                return opt_t(child);
        }

        return opt_t();
    }


} } // namespace pstade::lime


#endif
