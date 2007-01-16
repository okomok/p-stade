#ifndef PSTADE_OVEN_SET_MINUS_HPP
#define PSTADE_OVEN_SET_MINUS_HPP


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/unused.hpp>
#include "./merged.hpp"


namespace pstade { namespace oven {


namespace set_minus_detail {


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


} // namespace set_minus_detail


PSTADE_OVEN_DETAIL_MERGE_ADAPTOR(set_minus, set_minus_detail::merge_routine)


} } // namespace pstade::oven


#endif
