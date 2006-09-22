#ifndef PSTADE_OVEN_SHIFT_RANGE_HPP
#define PSTADE_OVEN_SHIFT_RANGE_HPP


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/egg/function.hpp>
#include <pstade/egg/pipable.hpp>
#include "./as_lightweight_proxy.hpp"
#include "./detail/concept_check.hpp"
#include "./range_difference.hpp"
#include "./slice_range.hpp"


namespace pstade { namespace oven {


namespace shift_range_detail {


    template< class ForwardRange >
    struct super_
    {
        typedef slice_range<ForwardRange> type;
    };


} // namespace shift_range_detail


template< class ForwardRange >
struct shift_range :
    shift_range_detail::super_<ForwardRange>::type,
    private as_lightweight_proxy< shift_range<ForwardRange> >
{
    typedef ForwardRange pstade_oven_range_base_type;

private:
    PSTADE_OVEN_DETAIL_REQUIRES(ForwardRange, ForwardRangeConcept);
    typedef typename shift_range_detail::super_<ForwardRange>::type super_t;
    typedef typename range_difference<ForwardRange>::type diff_t;

public:
    shift_range(ForwardRange& rng, diff_t d) :
        super_t(rng, d, d)
    { }
};


namespace shift_range_detail {


    struct baby_make
    {
        template< class Unused, class ForwardRange, class Difference >
        struct apply
        {
            typedef shift_range<ForwardRange> const type;
        };

        template< class Result, class ForwardRange, class Difference >
        Result call(ForwardRange& rng, Difference d)
        {
            return Result(rng, d);
        }
    };


} // namespace shift_range_detail


PSTADE_EGG_FUNCTION(make_shift_range, shift_range_detail::baby_make)
PSTADE_EGG_PIPABLE(shifted, shift_range_detail::baby_make)


} } // namespace pstade::oven


#endif
