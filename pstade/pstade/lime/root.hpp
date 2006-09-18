#ifndef PSTADE_LIME_ROOT_HPP
#define PSTADE_LIME_ROOT_HPP


// PStade.Lime
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/optional.hpp>
#include <pstade/oven/range_reference.hpp>


namespace pstade { namespace lime {


template< class Node >
typename oven::range_reference<Node>::type
root(Node& node)
{
    typedef typename oven::range_reference<Node>::type ref_t;
    boost::optional<ref_t> pa = node.parent();
    if (!pa)
        return node;

    return lime::root(*pa);
}


} } // namespace pstade::lime


#endif
