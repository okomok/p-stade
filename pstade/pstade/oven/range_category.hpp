#ifndef PSTADE_OVEN_RANGE_CATEGORY_HPP
#define PSTADE_OVEN_RANGE_CATEGORY_HPP


// PStade.Oven
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/iterator/iterator_traits.hpp> // iterator_category
#include "./range_iterator.hpp"


namespace pstade { namespace oven {


template< class Range >
struct range_category :
    boost::iterator_category<
        typename range_iterator<Range>::type
    >
{ };


} } // namespace pstade::oven


#endif
