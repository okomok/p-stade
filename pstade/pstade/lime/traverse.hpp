#ifndef PSTADE_LIME_TRAVERSE_HPP
#define PSTADE_LIME_TRAVERSE_HPP


// PStade.Lime
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/foreach.hpp>
#include <pstade/oven/range_reference.hpp>


namespace pstade { namespace lime {


    template< class Node, class UnaryFun >
    void traverse(Node& parent, UnaryFun fun)
    {
        typedef typename oven::range_reference<Node>::type child_t;

        BOOST_FOREACH (child_t child, parent) {
            traverse(child, fun);
            fun(child);
        }

        fun(parent);
    }


} } // namespace pstade::lime


#endif
