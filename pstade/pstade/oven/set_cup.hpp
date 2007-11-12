#ifndef PSTADE_OVEN_SET_CUP_HPP
#define PSTADE_OVEN_SET_CUP_HPP
#include "./detail/prefix.hpp"


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include "./detail/baby_to_adaptor.hpp"
#include "./merged.hpp"
#include "./read.hpp"


namespace pstade { namespace oven {


namespace set_cup_detail {


    struct merge_routine :
        merged_detail::merge_routine
    {
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
            else if (comp(read(first1), read(first2)))
                ++first1;
            else {
                ++first1;
                ++first2;
            }
        }
    };


} // namespace set_cup_detail


PSTADE_OVEN_BABY_TO_ADAPTOR(set_cup, (X_make_merged<set_cup_detail::merge_routine>::baby_type))


} } // namespace pstade::oven


#endif
