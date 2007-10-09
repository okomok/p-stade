#ifndef PSTADE_OVEN_ALGORITHM_HPP
#define PSTADE_OVEN_ALGORITHM_HPP
#include "./detail/prefix.hpp"


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)


// Note:
//
// I doubt the optimization using member functions is useful.
// Adaptors easily loses the base range type.


// References:
//
// [1] Eric Niebler, Boost.RangeEx, 2004.
//     http://www.boost-consulting.com/vault/index.php?directory=Algorithms


#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/seq/for_each.hpp>
#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>
#include <pstade/adl_barrier.hpp>
#include <pstade/egg/function.hpp>
#include <pstade/pass_by.hpp>
#include <pstade/pod_constant.hpp>
#include "./detail/lambda_algorithm.hpp"
#include "./detail/range_based_ll.hpp"


namespace pstade { namespace oven {


#define PSTADE_nonmodifying1 \
    (for_each)(find)(find_if)(adjacent_find)(count)(count_if)(mismatch)(equal) \
/**/

#define PSTADE_nonmodifying2 \
    (find_end)(find_first_of)(search) \
/**/


#define PSTADE_mutating1 \
    (copy)(copy_backward)(swap_ranges)(transform)(replace)(replace_if)(replace_copy)(replace_copy_if) \
    (fill)(generate)(remove)(remove_if)(remove_copy)(remove_copy_if)(unique)(unique_copy) \
    (reverse)(reverse_copy)(random_shuffle)(partition)(stable_partition) \
/**/
    // rejected... fill_n, generate_n
    // see below.. rotate, rotate_copy


#define PSTADE_sorting_and_related1 \
    (sort)(stable_sort)(lower_bound)(upper_bound)(equal_range)(binary_search) \
    (push_heap)(pop_heap)(make_heap)(sort_heap)(min_element)(max_element) \
    (next_permutation)(prev_permutation) \
/**/

#define PSTADE_sorting_and_related2 \
    (partial_sort_copy)(includes)(lexicographical_compare) \
    (merge)(set_union)(set_intersection)(set_difference)(set_symmetric_difference) \
/**/
    // see below.. partial_sort, nth_element, inplace_merge


#define PSTADE_partial_sort_form \
    (partial_sort)(nth_element)(inplace_merge) \
/**/


// 'partial_sort' etc use "middle".
#define PSTADE_range_based_partial_sort(R, _, Name) \
    struct BOOST_PP_CAT(baby_, Name) \
    { \
        template< class Myself, class Range, class MiddleFun, class Compare = void > \
        struct apply \
        { \
            typedef void type; \
        }; \
        \
        template< class Result, class Range, class MiddleFun, class Compare > \
        Result call(Range& rng, MiddleFun& fun, Compare& comp) const \
        { \
            return std::Name(boost::begin(rng), fun(rng), boost::end(rng), comp); \
        } \
        \
        template< class Result, class Range, class MiddleFun > \
        Result call(Range& rng, MiddleFun& fun) const \
        { \
            return std::Name(boost::begin(rng), fun(rng), boost::end(rng)); \
        } \
    }; \
    \
    typedef pstade::egg::function<BOOST_PP_CAT(baby_, Name)> BOOST_PP_CAT(T_, Name); \
    PSTADE_POD_CONSTANT((BOOST_PP_CAT(T_, Name)), Name) = {{}}; \
/**/


PSTADE_ADL_BARRIER(algorithm) {


    BOOST_PP_SEQ_FOR_EACH(PSTADE_OVEN_RANGE_BASED1_LL, ~, PSTADE_nonmodifying1)
    BOOST_PP_SEQ_FOR_EACH(PSTADE_OVEN_RANGE_BASED2_LL, ~, PSTADE_nonmodifying2)
    BOOST_PP_SEQ_FOR_EACH(PSTADE_OVEN_RANGE_BASED1_LL, ~, PSTADE_mutating1)
    BOOST_PP_SEQ_FOR_EACH(PSTADE_OVEN_RANGE_BASED1_LL, ~, PSTADE_sorting_and_related1)
    BOOST_PP_SEQ_FOR_EACH(PSTADE_OVEN_RANGE_BASED2_LL, ~, PSTADE_sorting_and_related2)
    BOOST_PP_SEQ_FOR_EACH(PSTADE_range_based_partial_sort, ~, PSTADE_partial_sort_form)


    // For some reason, they have the different names.

    struct baby_rotate
    {
        template< class Myself, class Range, class MiddleFun >
        struct apply
        {
            typedef void type;
        };

        template< class Result, class Range, class MiddleFun >
        void call(Range& rng, MiddleFun& fun) const
        {
            std::rotate(boost::begin(rng), fun(rng), boost::end(rng));
        }
    };

    typedef egg::function<baby_rotate> T_rotate;
    PSTADE_POD_CONSTANT((T_rotate), rotate) = {{}};

    struct baby_rotate_copy
    {
        template< class Myself, class Range, class MiddleFun, class OutIter >
        struct apply :
            pass_by_value<OutIter>
        { };

        template< class Result, class Range, class MiddleFun, class OutIter >
        Result call(Range& rng, MiddleFun& fun, OutIter& out) const
        {
            return std::rotate_copy(boost::begin(rng), fun(rng), boost::end(rng), out);
        }
    };

    typedef egg::function<baby_rotate_copy> T_rotate_copy;
    PSTADE_POD_CONSTANT((T_rotate_copy), rotate_copy) = {{}};


} // ADL barrier


#undef  PSTADE_range_based_partial_sort
#undef  PSTADE_partial_sort_form
#undef  PSTADE_sorting_and_related2
#undef  PSTADE_sorting_and_related1
#undef  PSTADE_mutating1
#undef  PSTADE_nonmodifying2
#undef  PSTADE_nonmodifying1


} } // namespace pstade::oven


#endif
