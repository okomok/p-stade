#ifndef PSTADE_OVEN_SET_DELTA_HPP
#define PSTADE_OVEN_SET_DELTA_HPP


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// Note:
//
// 'rng1|set_minus(rng2)|set_cup(rng2|set_minus(rng1))'
// works fine, but requires the ranges to be Forward.


#include <pstade/constant.hpp>
#include <pstade/pipable.hpp>
#include "./deref.hpp"
#include "./merged.hpp"


namespace pstade { namespace oven {


namespace set_delta_detail {


    struct merge_routine
    {
        template< class Iterator1, class Iterator2, class Compare >
        static void before_yield(
            Iterator1& first1, Iterator1 last1,
            Iterator2& first2, Iterator2 last2,
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
            Iterator1 const& first1, Iterator1 last1,
            Iterator2 const& first2, Iterator2 last2,
            Compare comp)
        {
            // copy-copy phase
            if (first1 == last1)
                return deref(first2);
            else if (first2 == last2)
                return deref(first1);

            // while phase
            return merged_detail::iter_min<Reference>(first1, first2, comp);
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
            if (comp(*first2, *first1))
                ++first2;
            else
                ++first1;
        }
    };


} // namespace set_delta_detail


typedef merged_detail::op_make<set_delta_detail::merge_routine> op_make_set_delta;
PSTADE_CONSTANT(make_set_delta, (op_make_set_delta))
PSTADE_PIPABLE(set_delta, (op_make_set_delta))


} } // namespace pstade::oven


#endif
