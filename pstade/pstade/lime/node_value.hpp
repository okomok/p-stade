#ifndef PSTADE_LIME_NODE_VALUE_HPP
#define PSTADE_LIME_NODE_VALUE_HPP


// PStade.Lime
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/oven/range_value.hpp>


namespace pstade { namespace lime {


template< class Node >
struct node_value :
    oven::range_value<Node>
{ };


} } // namespace pstade::lime


#endif
