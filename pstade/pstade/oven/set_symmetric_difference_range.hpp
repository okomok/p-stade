#ifndef PSTADE_OVEN_SET_SYMMETRIC_DIFFERENCE_RANGE_HPP
#define PSTADE_OVEN_SET_SYMMETRIC_DIFFERENCE_RANGE_HPP


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// Note:
//
// 'rng1|set_minus(rng2)|set_cup(rng2|set_minus(rng1))'
// works fine, but requires the ranges to be Forward.


#include <pstade/callable.hpp>
#include <pstade/functional.hpp> // less
#include <pstade/pass_by.hpp>
#include <pstade/pipable.hpp>
#include <pstade/singleton.hpp>
#include <pstade/unused.hpp>
#include "./as_lightweight_proxy.hpp"
#include "./concepts.hpp"
#include "./merge_range.hpp"


namespace pstade { namespace oven {


namespace set_symmetric_difference_range_detail {


    struct merge_routine
    {
        template< class Iterator1, class Iterator2, class Compare >
        static void before_yield(
            Iterator1& first1, Iterator1 const& last1,
            Iterator2& first2, Iterator2 const& last2,
            Compare comp)
        {
            while (first1 != last1 && first2 != last2) {
                if (comp(*first2, *first1))
                    break;
                else if (comp(*first1, *first2))
                    break;
                else {
                    ++first1;
                    ++first2;
                }
            }
        }

        template< class Reference, class Iterator1, class Iterator2, class Compare >
        static Reference yield(
            Iterator1 const& first1, Iterator1 const& last1,
            Iterator2 const& first2, Iterator2 const& last2,
            Compare& comp)
        {
            // copy-copy phase
            if (first1 == last1)
                return *first2;
            else if (first2 == last2)
                return *first1;

            // while phase
            return merge_iterator_detail::min_(*first1, *first2, comp);
        }

        template< class Iterator1, class Iterator2, class Compare >
        static void after_yield(
            Iterator1& first1, Iterator1 const& last1,
            Iterator2& first2, Iterator2 const& last2,
            Compare comp)
        {
            // copy-copy phase
            if (first1 == last1) {
                ++first2;
                return;
            }
            else if (first2 == last2) {
                ++first1;
                return;
            }

            // while phase
            if (comp(*first2, *first1))
                ++first2;
            else
                ++first1;
        }
    };


    template<
        class Range1, class Range2,
        class Compare
    >
    struct super_
    {
        typedef merge_range<
            Range1, Range2,
            Compare,
            merge_routine
        > type;
    };


} // namespace set_symmetric_difference_range_detail


template<
    class Range1, class Range2,
    class Compare = op_less
>
struct set_symmetric_difference_range :
    set_symmetric_difference_range_detail::super_<Range1, Range2, Compare>::type,
    private as_lightweight_proxy< set_symmetric_difference_range<Range1, Range2, Compare> >
{
    PSTADE_CONCEPT_ASSERT((SinglePass<Range1>));
    // PSTADE_CONCEPT_ASSERT((Readable<Range1>));
    PSTADE_CONCEPT_ASSERT((SinglePass<Range2>));
    // PSTADE_CONCEPT_ASSERT((Readable<Range2>));

private:
    typedef typename set_symmetric_difference_range_detail::super_<Range1, Range2, Compare>::type super_t;

public:
    set_symmetric_difference_range(Range1& rng1, Range2& rng2, Compare const& comp = pstade::less) :
        super_t(rng1, rng2, comp)
    { }
};


struct op_make_set_symmetric_difference_range :
    callable<op_make_set_symmetric_difference_range>
{
    template< class Myself, class Range1, class Range2, class Compare = op_less >
    struct apply
    {
        typedef typename pass_by_value<Compare>::type comp_t;
        typedef set_symmetric_difference_range<Range1, Range2, comp_t> const type;
    };

    template< class Result, class Range1, class Range2, class Compare >
    Result call(Range1& rng1, Range2& rng2, Compare& comp) const
    {
        return Result(rng1, rng2, comp);
    }

    template< class Result, class Range1, class Range2 >
    Result call(Range1& rng1, Range2& rng2) const
    {
        return Result(rng1, rng2);
    }
};


PSTADE_SINGLETON_CONST(make_set_symmetric_difference_range, op_make_set_symmetric_difference_range)
PSTADE_PIPABLE(set_delta, op_make_set_symmetric_difference_range)


} } // namespace pstade::oven


#endif
