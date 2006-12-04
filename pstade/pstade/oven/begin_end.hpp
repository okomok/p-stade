#ifndef PSTADE_OVEN_BEGIN_END_HPP
#define PSTADE_OVEN_BEGIN_END_HPP


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
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
#include <pstade/pipable.hpp>
#include "./range_iterator.hpp"


namespace pstade { namespace oven {


namespace begin_end_detail {


    struct with_apply
    {
        template< class Myself, class Range >
        struct apply :
            range_iterator<Range>
        { };
    };


    struct baby_begin : with_apply
    {
        template< class Result, class Range >
        Result call(Range& rng) const
        {
            return boost::begin(rng);
        }
    };


    struct baby_end   : with_apply
    {
        template< class Result, class Range >
        Result call(Range& rng) const
        {
            return boost::end(rng);
        }
    };


} // namespace begin_end_detail


PSTADE_ADL_BARRIER(begin_end) { // for Boost v1.33 'boost::const_begin/end'

PSTADE_EGG_FUNCTION(begin, begin_end_detail::baby_begin)
PSTADE_EGG_FUNCTION(end,   begin_end_detail::baby_end)

} // ADL barrier


PSTADE_PIPABLE(begins, begin_fun)
PSTADE_PIPABLE(ends,   end_fun)


} } // namespace pstade::oven


#endif
