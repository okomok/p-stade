#ifndef PSTADE_OVEN_SUB_RANGE_BASE_HPP
#define PSTADE_OVEN_SUB_RANGE_BASE_HPP


// PStade.Oven
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// Same as:
//
// boost::sub_range<Range>::base that is undocumented


// Note:
//
// Range-adaptors should not propagate const-ness using 'sub_range',
// because they can be temporaries. So, 'iterator_range' is used.


#include <boost/range/iterator_range.hpp>
#include "./range_iterator.hpp"


namespace pstade { namespace oven {


template< class Range >
struct sub_range_base
{
    typedef boost::iterator_range<
        typename range_iterator<Range>::type
    > type;
};


} } // namespace pstade::oven


#endif
