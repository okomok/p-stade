#ifndef PSTADE_OVEN_SORT_RANGE_HPP
#define PSTADE_OVEN_SORT_RANGE_HPP


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/ptr_container/indirect_fun.hpp>
#include <pstade/egg/by_value.hpp>
#include <pstade/egg/function.hpp>
#include <pstade/egg/pipable.hpp>
#include "./algorithm.hpp" // sort
#include "./as_lightweight_proxy.hpp"
#include "./detail/concept_check.hpp"
#include "./detail/less_than.hpp"
#include "./out_place_range.hpp"


namespace pstade { namespace oven {


namespace sort_range_detail {


    template< class BinaryPred >
    struct sort_fun
    {
        explicit sort_fun(BinaryPred pred) :
            m_pred(pred)
        { }

        template< class Range >
        void operator()(Range& its) const
        {
            oven::sort(its, boost::make_indirect_fun(m_pred));
        }

    private:
        BinaryPred m_pred;
    };


    template< class ForwardRange, class BinaryPred >
    struct super_
    {
        typedef out_place_range<
            ForwardRange, sort_fun<BinaryPred>
        > type;
    };


} // namespace sort_range_detail


template< class ForwardRange, class BinaryPred = detail::less_than_fun >
struct sort_range :
    sort_range_detail::super_<ForwardRange, BinaryPred>::type,
    private as_lightweight_proxy< sort_range<ForwardRange, BinaryPred> >
{
    typedef ForwardRange pstade_oven_range_base_type;

private:
    PSTADE_OVEN_DETAIL_REQUIRES(ForwardRange, ForwardRangeConcept);
    typedef typename sort_range_detail::super_<ForwardRange, BinaryPred>::type super_t;

public:
    explicit sort_range(ForwardRange& rng, BinaryPred pred = detail::less_than) :
        super_t(rng, sort_range_detail::sort_fun<BinaryPred>(pred))
    { }
};


namespace sort_range_detail {


    struct baby_generator
    {
        template< class Unused, class ForwardRange, class BinaryPred = detail::less_than_fun >
        struct result
        {
            typedef typename egg::by_value<BinaryPred>::type pred_t;
            typedef sort_range<ForwardRange, pred_t> const type;
        };

        template< class Result, class ForwardRange, class BinaryPred >
        Result call(ForwardRange& rng, BinaryPred& pred)
        {
            return Result(rng, pred);
        }

        template< class Result, class ForwardRange >
        Result call(ForwardRange& rng)
        {
            return Result(rng);
        }
    };


} // namespace sort_range_detail


PSTADE_EGG_FUNCTION(make_sort_range, sort_range_detail::baby_generator)
PSTADE_EGG_PIPABLE(sorted, sort_range_detail::baby_generator)


} } // namespace pstade::oven


#endif
