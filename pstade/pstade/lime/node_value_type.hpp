#ifndef PSTADE_LIME_NODE_VALUE_TYPE_HPP
#define PSTADE_LIME_NODE_VALUE_TYPE_HPP


// PStade.Lime
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/range/value_type.hpp>


namespace pstade { namespace lime {


template< class Node >
struct node_value :
    boost::range_value<Node>
{ };


} } // namespace pstade::lime


#endif
