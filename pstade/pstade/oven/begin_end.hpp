#ifndef PSTADE_OVEN_BEGIN_END_HPP
#define PSTADE_OVEN_BEGIN_END_HPP


// PStade.Oven
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// What:
//
// Provides functor version and pipable interface.


#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>
#include <pstade/adl_barrier.hpp>
#include <pstade/egg/function.hpp>
#include <pstade/egg/pipable.hpp>
#include "./range_iterator.hpp"


namespace pstade { namespace oven {


namespace begin_end_detail {


    struct gift
    {
        template< class Unused, class Range >
        struct result :
            range_iterator<Range>
        { };
    };


    struct baby_begin : gift
    {
        template< class Result, class Range >
        Result call(Range& rng)
        {
            return boost::begin(rng);
        }
    };


    struct baby_end : gift
    {
        template< class Result, class Range >
        Result call(Range& rng)
        {
            return boost::end(rng);
        }
    };


} // namespace begin_end_detail


PSTADE_ADL_BARRIER(begin_end) { // for Boost v1.33 'boost::const_begin/end'

PSTADE_EGG_FUNCTION(begin, begin_end_detail::baby_begin)
PSTADE_EGG_FUNCTION(end,   begin_end_detail::baby_end)

} // ADL barrier


PSTADE_EGG_PIPABLE(begins, begin_end_detail::baby_begin)
PSTADE_EGG_PIPABLE(ends,   begin_end_detail::baby_end)


} } // namespace pstade::oven


#endif
