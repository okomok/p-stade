#ifndef PSTADE_OVEN_RANGE_VALUE_TYPE_HPP
#define PSTADE_OVEN_RANGE_VALUE_TYPE_HPP


// PStade.Oven
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/iterator/iterator_traits.hpp>
#include "./range_iterator_type.hpp"


namespace pstade { namespace oven {


template< class Range >
struct range_value :
    boost::iterator_value<
        typename range_iterator<Range>::type
    >
{ };


} } // namespace pstade::oven


#endif
