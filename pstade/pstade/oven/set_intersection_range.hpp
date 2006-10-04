#ifndef PSTADE_OVEN_SET_INTERSECTION_RANGE_HPP
#define PSTADE_OVEN_SET_INTERSECTION_RANGE_HPP


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>
#include <boost/range/iterator_range.hpp>
#include <pstade/egg/function.hpp>
#include <pstade/egg/pipable.hpp>
#include <pstade/functional.hpp> // less
#include <pstade/pass_by.hpp>
#include <pstade/unused.hpp>
#include "./as_lightweight_proxy.hpp"
#include "./detail/concept_check.hpp"
#include "./merge_iterator.hpp"
#include "./range_iterator.hpp"


namespace pstade { namespace oven {


namespace set_intersection_range_detail {


    struct merge_routine
    {
        template< class Reference, class Iterator1, class Iterator2, class BinaryPred >
        static Reference yield(
            Iterator1 const& first1, Iterator1 const& last1,
            Iterator2 const& first2, Iterator2 const& last2,
            BinaryPred& pred)
        {
            pstade::unused(last1, first2, last2, pred);
            return *first1;
        }

        template< class Iterator1, class Iterator2, class BinaryPred >
        static void from_yield_phase(
            Iterator1& first1, Iterator1 const& last1,
            Iterator2& first2, Iterator2 const& last2,
            BinaryPred& pred)
        {
            pstade::unused(last1, last2, pred);
            ++first1;
            ++first2;
        }

        template< class Iterator1, class Iterator2, class BinaryPred >
        static void to_yield_phase(
            Iterator1& first1, Iterator1 const& last1,
            Iterator2& first2, Iterator2 const& last2,
            BinaryPred& pred)
        {
            while (first1 != last1 && first2 != last2)  {
                if (pred(*first2, *first1))
                    ++first2;
                else if (pred(*first1, *first2))
                    ++first1;
                else
                    break;
            }

            // no copy-copy phase
            if (first1 == last1)
                first2 = last2;
            if (first2 == last2)
                first1 = last1;
        }
    };


    template<
        class Range1, class Range2,
        class BinaryPred
    >
    struct super_
    {
        typedef boost::iterator_range<
            merge_iterator<
                typename range_iterator<Range1>::type,
                typename range_iterator<Range2>::type,
                BinaryPred,
                merge_routine
            >
        > type;
    };


} // namespace set_intersection_range_detail


template<
    class Range1, class Range2,
    class BinaryPred = less_fun
>
struct set_intersection_range :
    set_intersection_range_detail::super_<Range1, Range2, BinaryPred>::type,
    private as_lightweight_proxy< set_intersection_range<Range1, Range2, BinaryPred> >
{
    typedef Range1 pstade_oven_range_base_type;

private:
    PSTADE_OVEN_DETAIL_REQUIRES(Range1, SinglePassRangeConcept);
    PSTADE_OVEN_DETAIL_REQUIRES(Range2, SinglePassRangeConcept);
    typedef typename set_intersection_range_detail::super_<Range1, Range2, BinaryPred>::type super_t;
    typedef typename super_t::iterator iter_t;

public:
    set_intersection_range(Range1& rng1, Range2& rng2, BinaryPred const& pred = pstade::less) :
        super_t(
            iter_t(boost::begin(rng1), boost::end(rng1), boost::begin(rng2), boost::end(rng2), pred),
            iter_t(boost::end(rng1),   boost::end(rng1), boost::end(rng2),   boost::end(rng2), pred)
        )
    { }
};


namespace set_intersection_range_detail {


    struct baby_make
    {
        template< class Myself, class Range1, class Range2, class BinaryPred = less_fun >
        struct apply
        {
            typedef typename pass_by_value<BinaryPred>::type pred_t;
            typedef set_intersection_range<Range1, Range2, pred_t> const type;
        };

        template< class Result, class Range1, class Range2, class BinaryPred >
        Result call(Range1& rng1, Range2& rng2, BinaryPred& pred)
        {
            return Result(rng1, rng2, pred);
        }

        template< class Result, class Range1, class Range2 >
        Result call(Range1& rng1, Range2& rng2)
        {
            return Result(rng1, rng2);
        }
    };


} // namespace set_intersection_range_detail


PSTADE_EGG_FUNCTION(make_set_intersection_range, set_intersection_range_detail::baby_make)
PSTADE_EGG_PIPABLE(set_cap, set_intersection_range_detail::baby_make)


} } // namespace pstade::oven


#endif
