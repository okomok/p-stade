#ifndef PSTADE_OVEN_SET_MINUS_HPP
#define PSTADE_OVEN_SET_MINUS_HPP


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/constant.hpp>
#include <pstade/pipable.hpp>
#include <pstade/unused.hpp>
#include "./deref.hpp"
#include "./merged.hpp"


namespace pstade { namespace oven {


namespace set_minus_detail {


    struct merge_routine
    {
        template< class Iterator1, class Iterator2, class Compare >
        static void before_yield(
            Iterator1& first1, Iterator1 last1,
            Iterator2& first2, Iterator2 last2,
            Compare comp)
        {
            while (first1 != last1 && first2 != last2) {
                if (comp(deref(first2), deref(first1)))
                    ++first2;
                else if (comp(deref(first1), deref(first2)))
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
            Iterator1 const& first1, Iterator1 last1,
            Iterator2 const& first2, Iterator2 last2,
            Compare comp)
        {
            unused(last1, first2, last2, comp);
            return deref(first1);
        }

        template< class Iterator1, class Iterator2, class Compare >
        static void after_yield(
            Iterator1& first1, Iterator1 last1,
            Iterator2& first2, Iterator2 last2,
            Compare comp)
        {
            unused(last1, first2, last2, comp);
            ++first1;
        }
    };


} // namespace set_minus_detail


typedef merged_detail::op_make<set_minus_detail::merge_routine> op_make_set_minus;
PSTADE_CONSTANT(make_set_minus, (op_make_set_minus))
PSTADE_PIPABLE(set_minus, (op_make_set_minus))


} } // namespace pstade::oven


#endif
