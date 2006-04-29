#ifndef PSTADE_OVEN_EQUAL_HPP
#define PSTADE_OVEN_EQUAL_HPP


// PStade.Oven
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// Boost.RangeEx
//
// Copyright 2004 Eric Niebler.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// equals
//
// Copyright Pavol Droba 2002-2003. Use, modification and
// distribution is subject to the Boost Software License, Version
// 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <algorithm> // equal
#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>
#include <boost/range/const_iterator.hpp>
#include <pstade/egg/function.hpp>
#include "./detail/equal_to.hpp"


namespace pstade { namespace oven {


namespace equal_detail {


    struct gift
    {
        template< class Range, class InputIterOrRange, class BinaryPred = void >
        struct result
        {
            typedef bool type;
        };
    };


    struct baby : gift
    {
        template< class Result, class Range, class InputIter, class BinaryPred >
        Result call(const Range& rng, InputIter first, BinaryPred pred)
        {
            return std::equal(boost::begin(rng), boost::end(rng), first, pred);
        }

        template< class Result, class Range, class InputIter >
        Result call(const Range& rng, InputIter first)
        {
            return std::equal(boost::begin(rng), boost::end(rng), first);
        }
    };


    struct range_baby : gift
    {
        template< class Result, class Range1, class Range2, class BinaryPred >
        Result call(const Range1& rng1, const Range2& rng2, BinaryPred pred)
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

        template< class Result, class Range1, class Range2 >
        Result call(const Range1& rng1, const Range2& rng2)
        {
            return call<Result>(rng1, rng2, detail::equal_to());
        }
    };


} // namespace equal_detail


PSTADE_EGG_FUNCTION(equal, equal_detail::baby)
PSTADE_EGG_FUNCTION(equals, equal_detail::range_baby)


} } // namespace pstade::oven


#endif
