#ifndef PSTADE_OVEN_SET_CAP_HPP
#define PSTADE_OVEN_SET_CAP_HPP


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/constant.hpp>
#include <pstade/pipable.hpp>
#include <pstade/unused.hpp>
#include "./merged.hpp"


namespace pstade { namespace oven {


namespace set_cap_detail {


    struct merge_routine
    {
        template< class Iterator1, class Iterator2, class Compare >
        static void before_yield(
            Iterator1& first1, Iterator1 last1,
            Iterator2& first2, Iterator2 last2,
            Compare comp)
        {
            while (first1 != last1 && first2 != last2)  {
                if (comp(*first2, *first1))
                    ++first2;
                else if (comp(*first1, *first2))
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
        
        template< class Reference, class Iterator1, class Iterator2, class Compare >
        static Reference yield(
            Iterator1 first1, Iterator1 last1,
            Iterator2 first2, Iterator2 last2,
            Compare comp)
        {
            unused(last1, first2, last2, comp);
            return *first1;
        }

        template< class Iterator1, class Iterator2, class Compare >
        static void after_yield(
            Iterator1& first1, Iterator1 last1,
            Iterator2& first2, Iterator2 last2,
            Compare comp)
        {
            unused(last1, last2, comp);
            ++first1;
            ++first2;
        }
    };


} // namespace set_cap_detail


typedef op_make_merged<set_cap_detail::merge_routine> op_make_set_cap;
PSTADE_CONSTANT(make_set_cap, (op_make_set_cap))
PSTADE_PIPABLE(set_cap, (op_make_set_cap))


} } // namespace pstade::oven


#endif
