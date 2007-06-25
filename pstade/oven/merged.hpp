#ifndef PSTADE_OVEN_MERGED_HPP
#define PSTADE_OVEN_MERGED_HPP
#include "./detail/prefix.hpp"


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// Note:
//
// This range is Constant.
// If a value referenced by this iterator is changed,
// the incementing way is changed.
// Then, the iterators become incompatible.


#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>
#include <pstade/callable.hpp>
#include <pstade/constant.hpp>
#include <pstade/functional.hpp> // less
#include <pstade/pass_by.hpp>
#include <pstade/unused.hpp>
#include "./concepts.hpp"
#include "./detail/merge_iterator.hpp"
#include "./iter_range.hpp"
#include "./range_iterator.hpp"
#include "./read.hpp"


namespace pstade { namespace oven {


namespace merged_detail {


    namespace here = merged_detail;


    // Pass by reference; see "./reverse_iterator.hpp".
    template< class Reference, class Iterator1, class Iterator2, class Compare > 
    Reference iter_min(Iterator1 const& it1, Iterator2 const& it2, Compare comp)
    {
        // ternary-operator could make a rvalue.
        // I don't certainly know, though.

        // Standard requires '*it1' if equal.
        if (comp(read(it2), read(it1)))
            return read(it2);
        else
            return read(it1);
    }


    // This code is generated from STL implementation
    // somewhat by rote.
    struct merge_routine
    {
        template< class Iterator1, class Iterator2, class Compare >
        static void before_yield(
            Iterator1& first1, Iterator1 last1,
            Iterator2& first2, Iterator2 last2,
            Compare comp)
        {
            /* has no effect.
            while (first1 != last1 && first2 != last2) {
                if (comp(*first2, *first1)) 
                    break;
                else
                    break;
            }
            */
            unused(first1, last1, first2, last2, comp);
        }

        template< class Reference, class Iterator1, class Iterator2, class Compare >
        static Reference yield(
            Iterator1 const& first1, Iterator1 last1,
            Iterator2 const& first2, Iterator2 last2,
            Compare comp)
        {
            // copy-copy phase
            if (first1 == last1)
                return read(first2);
            else if (first2 == last2)
                return read(first1);

            // while phase
            return here::iter_min<Reference>(first1, first2, comp);
        }

        template< class Iterator1, class Iterator2, class Compare >
        static void after_yield(
            Iterator1& first1, Iterator1 last1,
            Iterator2& first2, Iterator2 last2,
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
            if (comp(read(first2), read(first1)))
                ++first2;
            else
                ++first1;
        }
    };


    template< class MergeRoutine >
    struct op_make :
        callable< op_make<MergeRoutine> >
    {
        template< class Myself, class Range1, class Range2, class Compare = op_less const >
        struct apply
        {
            typedef
                detail::merge_iterator<
                    typename range_iterator<Range1>::type,
                    typename range_iterator<Range2>::type,
                    typename pass_by_value<Compare>::type,
                    MergeRoutine
                >
            iter_t;

            typedef
                iter_range<iter_t> const
            type;
        };

        template< class Result, class Range1, class Range2, class Compare >
        Result call(Range1& rng1, Range2& rng2, Compare& comp) const
        {
            PSTADE_CONCEPT_ASSERT((SinglePass<Range1>));
            PSTADE_CONCEPT_ASSERT((SinglePass<Range2>));

            typedef typename Result::iterator iter_t;
            return aux<Result>(boost::begin(rng1), boost::end(rng1), boost::begin(rng2), boost::end(rng2), comp);
        }

        template< class Result, class Range1, class Range2 >
        Result call(Range1& rng1, Range2& rng2) const
        {
            return (*this)(rng1, rng2, less);
        }

        template< class Result, class Iterator1, class Iterator2, class Compare >
        Result aux(Iterator1 first1, Iterator1 last1, Iterator2 first2, Iterator2 last2, Compare& comp) const
        {
            typedef typename Result::iterator iter_t;
            return Result(iter_t(first1, last1, first2, last2, comp), iter_t(last1, last1, last2, last2, comp));
        }
    };


} // namespace merged_detail


typedef merged_detail::op_make<merged_detail::merge_routine> op_make_merged;
PSTADE_CONSTANT(make_merged, (op_make_merged))
PSTADE_PIPABLE(merged, (op_make_merged))


} } // namespace pstade::oven


#endif
