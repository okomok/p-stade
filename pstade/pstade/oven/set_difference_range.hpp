#ifndef PSTADE_OVEN_SET_DIFFERENCE_RANGE_HPP
#define PSTADE_OVEN_SET_DIFFERENCE_RANGE_HPP


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/functional.hpp> // less
#include <pstade/object_generator.hpp>
#include <pstade/pipable.hpp>
#include <pstade/unused.hpp>
#include "./as_lightweight_proxy.hpp"
#include "./concepts.hpp"
#include "./merge_range.hpp"


namespace pstade { namespace oven {


namespace set_difference_range_detail {


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
                    ++first2;
                else if (comp(*first1, *first2))
                    break;
                else {
                    ++first1;
                    ++first2;
                }
            }

            // no copy phase of rng2
            if (first1 == last1)
                first2 = last2;
        }

        template< class Reference, class Iterator1, class Iterator2, class Compare >
        static Reference yield(
            Iterator1 const& first1, Iterator1 const& last1,
            Iterator2 const& first2, Iterator2 const& last2,
            Compare& comp)
        {
            pstade::unused(last1, first2, last2, comp);
            return *first1;
        }

        template< class Iterator1, class Iterator2, class Compare >
        static void after_yield(
            Iterator1& first1, Iterator1 const& last1,
            Iterator2& first2, Iterator2 const& last2,
            Compare& comp)
        {
            pstade::unused(last1, first2, last2, comp);
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


} // namespace set_difference_range_detail


template<
    class Range1, class Range2,
    class Compare = op_less
>
struct set_difference_range :
    set_difference_range_detail::super_<Range1, Range2, Compare>::type,
    private as_lightweight_proxy< set_difference_range<Range1, Range2, Compare> >
{
    PSTADE_CONCEPT_ASSERT((SinglePass<Range1>));
    // PSTADE_CONCEPT_ASSERT((Readable<Range1>));
    PSTADE_CONCEPT_ASSERT((SinglePass<Range2>));
    // PSTADE_CONCEPT_ASSERT((Readable<Range2>));
    typedef set_difference_range type;

private:
    typedef typename set_difference_range_detail::super_<Range1, Range2, Compare>::type super_t;

public:
    set_difference_range(Range1& rng1, Range2& rng2, Compare const& comp = pstade::less) :
        super_t(rng1, rng2, comp)
    { }
};

PSTADE_OBJECT_GENERATOR(make_set_difference_range,
    (set_difference_range< deduce_to_qualified<from_1>, deduce_to_qualified<from_2>, deduce_to_value<from_3, op_less> >) const)
PSTADE_PIPABLE(set_minus, (op_make_set_difference_range))


} } // namespace pstade::oven


#endif
