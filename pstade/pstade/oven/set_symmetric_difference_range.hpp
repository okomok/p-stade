#ifndef PSTADE_OVEN_SET_SYMMETRIC_DIFFERENCE_RANGE_HPP
#define PSTADE_OVEN_SET_SYMMETRIC_DIFFERENCE_RANGE_HPP


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// Todo:
//
// This range, for now, needs ForwardRange.
// The implementation seems beautiful, though.


#include <pstade/egg/function.hpp>
#include <pstade/egg/pipable.hpp>
#include <pstade/functional.hpp> // less
#include <pstade/pass_by.hpp>
#include "./as_lightweight_proxy.hpp"
#include "./detail/concept_check.hpp"
#include "./set_difference_range.hpp"
#include "./set_union_range.hpp"


namespace pstade { namespace oven {


namespace set_symmetric_difference_range_detail {


    template<
        class ForwardRange1, class ForwardRange2,
        class BinaryPred
    >
    struct super_
    {
        typedef set_union_range<
            set_difference_range<ForwardRange1, ForwardRange2, BinaryPred> const,
            set_difference_range<ForwardRange2, ForwardRange1, BinaryPred> const
        > type;
    };


} // namespace set_symmetric_difference_range_detail


template<
    class ForwardRange1, class ForwardRange2,
    class BinaryPred = less_fun
>
struct set_symmetric_difference_range :
    set_symmetric_difference_range_detail::super_<ForwardRange1, ForwardRange2, BinaryPred>::type,
    private as_lightweight_proxy< set_symmetric_difference_range<ForwardRange1, ForwardRange2, BinaryPred> >
{
    typedef ForwardRange1 pstade_oven_range_base_type;

private:
    PSTADE_OVEN_DETAIL_REQUIRES(ForwardRange1, SinglePassForwardRangeConcept);
    PSTADE_OVEN_DETAIL_REQUIRES(ForwardRange2, SinglePassForwardRangeConcept);
    typedef typename set_symmetric_difference_range_detail::super_<ForwardRange1, ForwardRange2, BinaryPred>::type super_t;

public:
    set_symmetric_difference_range(ForwardRange1& rng1, ForwardRange2& rng2, BinaryPred const& pred = pstade::less) :
        super_t(rng1|set_minus(rng2, pred), rng2|set_minus(rng1, pred))
    { }
};


namespace set_symmetric_difference_range_detail {


    struct baby_make
    {
        template< class Myself, class ForwardRange1, class ForwardRange2, class BinaryPred = less_fun >
        struct apply
        {
            typedef typename pass_by_value<BinaryPred>::type pred_t;
            typedef set_symmetric_difference_range<ForwardRange1, ForwardRange2, pred_t> const type;
        };

        template< class Result, class ForwardRange1, class ForwardRange2, class BinaryPred >
        Result call(ForwardRange1& rng1, ForwardRange2& rng2, BinaryPred& pred)
        {
            return Result(rng1, rng2, pred);
        }

        template< class Result, class ForwardRange1, class ForwardRange2 >
        Result call(ForwardRange1& rng1, ForwardRange2& rng2)
        {
            return Result(rng1, rng2);
        }
    };


} // namespace set_symmetric_difference_range_detail


PSTADE_EGG_FUNCTION(make_set_symmetric_difference_range, set_symmetric_difference_range_detail::baby_make)
PSTADE_EGG_PIPABLE(set_delta, set_symmetric_difference_range_detail::baby_make)


} } // namespace pstade::oven


#endif
