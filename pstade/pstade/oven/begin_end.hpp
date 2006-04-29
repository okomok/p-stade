#ifndef PSTADE_OVEN_BEGIN_END_HPP
#define PSTADE_OVEN_BEGIN_END_HPP


// PStade.Oven
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>
#include <boost/range/result_iterator.hpp>
#include <pstade/adl_barrier.hpp>
#include <pstade/egg/function.hpp>
#include "./range_adaptor.hpp"


namespace pstade { namespace oven {


namespace begin_end_detail {


    struct gift
    {
        template< class Range >
        struct result :
            boost::range_result_iterator<Range>
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


PSTADE_ADL_BARRIER_OPEN(begin_end) // for boost::const_begin/end

    PSTADE_EGG_FUNCTION(begin, begin_end_detail::baby_begin)
    PSTADE_EGG_FUNCTION(end, begin_end_detail::baby_end)

PSTADE_ADL_BARRIER_CLOSE(begin_end)


PSTADE_OVEN_RANGE_ADAPTOR(begun, begin_end_detail::baby_begin)
PSTADE_OVEN_RANGE_ADAPTOR(ended, begin_end_detail::baby_end)


} } // namespace pstade::oven


#endif
