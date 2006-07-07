#ifndef PSTADE_OVEN_EQUALS_HPP
#define PSTADE_OVEN_EQUALS_HPP


// PStade.Oven
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// See: 'equals' at Boost.StringAlgorithm
//
// Copyright Pavol Droba 2002-2003. Use, modification and
// distribution is subject to the Boost Software License, Version
// 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>
#include <boost/range/const_iterator.hpp>
#include "./detail/equal_to.hpp"


namespace pstade { namespace oven {


template< class Range1, class Range2, class BinaryPred >
bool equals(Range1 const& rng1, Range2 const& rng2, BinaryPred pred)
{
    typedef typename boost::range_const_iterator<Range1>::type iter1_t;
    typedef typename boost::range_const_iterator<Range2>::type iter2_t;

    iter1_t it1 = boost::const_begin(rng1), last1 = boost::const_end(rng1);
    iter2_t it2 = boost::const_begin(rng2), last2 = boost::const_end(rng2);

    for (; it1 != last1 && it2 != last2; ++it1, ++it2) {
        if (!pred(*it1, *it2))
            return false;
    }

    return (it2 == last2) && (it1 == last1);
}


template< class Range1, class Range2 > inline
bool equals(Range1 const& rng1, Range2 const& rng2)
{
    return oven::equals(rng1, rng2, detail::equal_to);
}


} } // namespace pstade::oven


#endif
