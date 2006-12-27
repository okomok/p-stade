#ifndef PSTADE_OVEN_ALGORITHM_HPP
#define PSTADE_OVEN_ALGORITHM_HPP


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)


// Port of: Boost.RangeEx
//
// Copyright 2004 Eric Niebler.
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
// (C) Copyright Thorsten Ottosen 2002-3. Permission to copy, use, modify,
// sell and distribute this software is granted provided this
// copyright notice appears in all copies. This software is provided
// "as is" without express or implied warranty, and with no claim as
// to its suitability for any purpose.
//
// (C) Copyright Jeremy Siek 2001. Permission to copy, use, modify,
// sell and distribute this software is granted provided this
// copyright notice appears in all copies. This software is provided
// "as is" without express or implied warranty, and with no claim as
// to its suitability for any purpose.
//
// Mutating algorithms originally written by Vladimir Prus'
// <ghost@cs.msu.su> code from Boost Wiki
//
// Problem: should member functions be called automatically? Or should the user
// know that it is better to call map::find() than find( map )?


#include <algorithm>
#include <utility> // pair
#include <boost/mpl/identity.hpp>
#include <boost/preprocessor/cat.hpp>
#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>
#include <pstade/adl_barrier.hpp>
#include <pstade/apple/has_equal_range.hpp>
#include <pstade/apple/has_find.hpp>
#include <pstade/apple/has_lower_bound.hpp>
#include <pstade/apple/has_remove.hpp>
#include <pstade/apple/has_remove_if.hpp>
#include <pstade/apple/has_reverse.hpp>
#include <pstade/apple/has_sort.hpp>
#include <pstade/apple/has_unique.hpp>
#include <pstade/apple/has_upper_bound.hpp>
#include <pstade/callable.hpp>
#include <pstade/constant.hpp>
#include <pstade/enable_if.hpp>
#include <pstade/pass_by.hpp>
#include "./detail/forward.hpp"
#include "./range_difference.hpp"
#include "./range_iterator.hpp"


namespace pstade { namespace oven {


PSTADE_ADL_BARRIER(algorithm) {


    // Non-Modifying Sequence Operations


    // for_each

    PSTADE_OVEN_DETAIL_FORWARD(for_each, std::for_each, (pass_by_value<A0>), (1))


    // find
    
    struct op_find :
        callable<op_find>
    {
        template< class Myself, class Range, class Val >
        struct apply :
            range_iterator<Range>
        { };

        template< class Result, class Range, class Val >
        Result call(Range& rng, Val& val,
            // GCC fails if 'enable_if' is placed on result type. 
            typename enable_if< apple::has_find<Range> >::type = 0) const
        {
            return rng.find(val);
        }

        template< class Result, class Range, class Val >
        Result call(Range& rng, Val& val,
            typename disable_if<apple::has_find<Range> >::type = 0) const
        {
            return std::find(boost::begin(rng), boost::end(rng), val);
        }
    };

    PSTADE_CONSTANT(find, (op_find))


    // find_if

    PSTADE_OVEN_DETAIL_FORWARD(find_if, std::find_if, (range_iterator<Range>), (1))


    // find_end/find_first_of

    PSTADE_OVEN_DETAIL_FORWARD_BINARY(find_end,      std::find_end,      (range_iterator<Range1>), (0)(1))
    PSTADE_OVEN_DETAIL_FORWARD_BINARY(find_first_of, std::find_first_of, (range_iterator<Range1>), (0)(1))


    // adjacent_find

    PSTADE_OVEN_DETAIL_FORWARD(adjacent_find, std::adjacent_find, (range_iterator<Range>), (0)(1))


    // count(_if)

    PSTADE_OVEN_DETAIL_FORWARD(count,    std::count,    (range_difference<Range>), (1))
    PSTADE_OVEN_DETAIL_FORWARD(count_if, std::count_if, (range_difference<Range>), (1))


    // mismatch

    template< class Range, class A0 >
    struct detail_mismatch_result
    {
        typedef
            std::pair<
                typename range_iterator<Range>::type,
                typename pass_by_value<A0>::type
            >
        type;
    };

    PSTADE_OVEN_DETAIL_FORWARD(mismatch, std::mismatch, (detail_mismatch_result<Range, A0>), (1)(2))


    // equal

    PSTADE_OVEN_DETAIL_FORWARD(equal, std::equal, (boost::mpl::identity<bool>), (1)(2))


    // search

    PSTADE_OVEN_DETAIL_FORWARD_BINARY(search, std::search, (range_iterator<Range1>), (0)(1))


    // Modifying Sequence Operations


    // copy(_backward)

    PSTADE_OVEN_DETAIL_FORWARD(copy,          std::copy,          (pass_by_value<A0>), (1))
    PSTADE_OVEN_DETAIL_FORWARD(copy_backward, std::copy_backward, (pass_by_value<A0>), (1))


    // transform

    struct op_transform :
        callable<op_transform>
    {
        template< class Myself, class Range, class InIter, class OutIter, class BinOp = void >
        struct apply :
            pass_by_value<OutIter>
        { };

        template< class Result, class Range, class InIter, class OutIter, class BinOp >
        Result call(Range& rng, InIter& first2, OutIter& out, BinOp& fun) const
        {
            return std::transform(boost::begin(rng), boost::end(rng), first2, out, fun);
        }

        template< class Myself, class Range, class OutIter, class UnaryOp >
        struct apply<Myself, Range, OutIter, UnaryOp> :
            pass_by_value<OutIter>
        { };

        template< class Result, class Range, class OutIter, class UnaryOp >
        Result call(Range& rng, OutIter& out, UnaryOp& fun) const
        {
            return std::transform(boost::begin(rng), boost::end(rng), out, fun);
        }
    };

    PSTADE_CONSTANT(transform, (op_transform))


    // replace(_if)/replace_copy(_if)

    PSTADE_OVEN_DETAIL_FORWARD(replace,         std::replace,         (boost::mpl::identity<void>), (2)) 
    PSTADE_OVEN_DETAIL_FORWARD(replace_if,      std::replace_if,      (boost::mpl::identity<void>), (2))
    PSTADE_OVEN_DETAIL_FORWARD(replace_copy,    std::replace_copy,    (pass_by_value<A0>), (3))
    PSTADE_OVEN_DETAIL_FORWARD(replace_copy_if, std::replace_copy_if, (pass_by_value<A0>), (3))


    // fill

    PSTADE_OVEN_DETAIL_FORWARD(fill, std::fill, (boost::mpl::identity<void>), (1))


    // fill_n

#define PSTADE_fill_n_form(Xxx, ResultFun) \
    \
    struct BOOST_PP_CAT(op_, Xxx) : \
        callable<BOOST_PP_CAT(op_, Xxx)> \
    { \
        template< class Myself, class Range, class A0, class A1 > \
        struct apply : \
            ResultFun \
        { }; \
        \
        template< class Result, class Range, class A0, class A1 > \
        Result call(Range& rng, A0& a0, A1& a1) const \
        { \
            std::Xxx(boost::begin(rng), a0, a1); \
        } \
    }; \
    \
    PSTADE_CONSTANT( Xxx, (BOOST_PP_CAT(op_, Xxx)) ) \
    \
/**/

    PSTADE_fill_n_form(fill_n, boost::mpl::identity<void>)


    // generate

    PSTADE_OVEN_DETAIL_FORWARD(generate, std::generate, (boost::mpl::identity<void>), (1))

    
    // generate_n

    PSTADE_fill_n_form(generate_n, boost::mpl::identity<void>)


    // remove

    struct op_remove :
        callable<op_remove>
    {
        template< class Myself, class Range, class Val >
        struct apply :
            range_iterator<Range>
        { };

        template< class Result, class Range, class Val >
        Result call(Range& rng, Val& val,
            typename enable_if< apple::has_remove<Range> >::type = 0) const
        {
            rng.remove(val);
            return boost::end(rng);
        }

        template< class Result, class Range, class Val >
        Result call(Range& rng, Val& val,
            typename disable_if<apple::has_remove<Range> >::type = 0) const
        {
            return std::remove(boost::begin(rng), boost::end(rng), val);
        }
    };

    PSTADE_CONSTANT(remove, (op_remove))


    // remove_if

    struct op_remove_if :
        callable<op_remove_if>
    {
        template< class Myself, class Range, class Pred >
        struct apply :
            range_iterator<Range>
        { };

        template< class Result, class Range, class Pred >
        Result call(Range& rng, Pred& pred,
            typename enable_if< apple::has_remove_if<Range> >::type = 0) const
        {
            rng.remove_if(pred);
            return boost::end(rng);
        }

        template< class Result, class Range, class Pred >
        Result call(Range& rng, Pred& pred,
            typename disable_if<apple::has_remove_if<Range> >::type = 0) const
        {
            return std::remove_if(boost::begin(rng), boost::end(rng), pred);
        }
    };

    PSTADE_CONSTANT(remove_if, (op_remove_if))


    // remove_copy(_if)

    PSTADE_OVEN_DETAIL_FORWARD(remove_copy,    std::remove_copy,    (pass_by_value<A0>), (2))
    PSTADE_OVEN_DETAIL_FORWARD(remove_copy_if, std::remove_copy_if, (pass_by_value<A0>), (2))


    // unique

    struct op_unique :
        callable<op_unique>
    {
        template< class Myself, class Range, class Pred = void >
        struct apply :
            range_iterator<Range>
        { };

        template< class Result, class Range, class Pred >
        Result call(Range& rng, Pred& pred,
            typename enable_if< apple::has_unique<Range> >::type = 0) const
        {
            rng.unique(pred);
            return boost::end(rng);
        }

        template< class Result, class Range, class Pred >
        Result call(Range& rng, Pred& pred,
            typename disable_if<apple::has_unique<Range> >::type = 0) const
        {
            return std::unique(boost::begin(rng), boost::end(rng), pred);
        }

        template< class Result, class Range >
        Result call(Range& rng,
            typename enable_if< apple::has_unique<Range> >::type = 0) const
        {
            rng.unique();
            return boost::end(rng);
        }

        template< class Result, class Range >
        Result call(Range& rng,
            typename disable_if<apple::has_unique<Range> >::type = 0) const
        {
            return std::unique(boost::begin(rng), boost::end(rng));
        }
    };

    PSTADE_CONSTANT(unique, (op_unique))


    // unique_copy

    PSTADE_OVEN_DETAIL_FORWARD(unique_copy, std::unique_copy, (pass_by_value<A0>), (1)(2))


    // reverse

    struct op_reverse :
        callable<op_reverse>
    {
        template< class Myself, class Range >
        struct apply
        {
            typedef void type;
        };

        template< class Result, class Range >
        void call(Range& rng,
            typename enable_if< apple::has_reverse<Range> >::type = 0) const
        {
            rng.reverse();
        }

        template< class Result, class Range >
        void call(Range& rng,
            typename disable_if<apple::has_reverse<Range> >::type = 0) const
        {
            std::reverse(boost::begin(rng), boost::end(rng));
        }
    };

    PSTADE_CONSTANT(reverse, (op_reverse))


    // reverse_copy

    PSTADE_OVEN_DETAIL_FORWARD(reverse_copy, std::reverse_copy, (pass_by_value<A0>), (1))


    // rotate

    struct op_rotate :
        callable<op_rotate>
    {
        template< class Myself, class Range, class Middle >
        struct apply
        {
            typedef void type;
        };

        template< class Result, class Range >
        void call(Range& rng, typename range_iterator<Range>::type const& middle) const
        {
            std::rotate(boost::begin(rng), middle, boost::end(rng));
        }
    };

    PSTADE_CONSTANT(rotate, (op_rotate))


    // rotate_copy

    struct op_rotate_copy :
        callable<op_rotate_copy>
    {
        template< class Myself, class Range, class Middle, class OutIter >
        struct apply :
            pass_by_value<OutIter>
        { };

        template< class Result, class Range, class OutIter >
        Result call(Range& rng, typename range_iterator<Range>::type const& middle, OutIter& out) const
        {
            return std::rotate_copy(boost::begin(rng), middle, boost::end(rng), out);
        }
    };

    PSTADE_CONSTANT(rotate_copy, (op_rotate_copy))


    // random_shuffle

    PSTADE_OVEN_DETAIL_FORWARD(random_shuffle, std::random_shuffle, (boost::mpl::identity<void>), (0)(1))


    // (stable_)partition

    PSTADE_OVEN_DETAIL_FORWARD(partition,        std::partition,        (range_iterator<Range>), (1))
    PSTADE_OVEN_DETAIL_FORWARD(stable_partition, std::stable_partition, (range_iterator<Range>), (1))


    // sort

    struct op_sort :
        callable<op_sort>
    {
        template< class Myself, class Range, class Cmp = void >
        struct apply
        {
            typedef void type;
        };

        template< class Result, class Range, class Cmp >
        void call(Range& rng, Cmp& cmp,
            typename enable_if< apple::has_sort<Range> >::type = 0) const
        {
            rng.sort(cmp);
        }

        template< class Result, class Range, class Cmp >
        void call(Range& rng, Cmp& cmp,
            typename disable_if<apple::has_sort<Range> >::type = 0) const
        {
            std::sort(boost::begin(rng), boost::end(rng), cmp);
        }

        template< class Result, class Range >
        void call(Range& rng,
            typename enable_if< apple::has_sort<Range> >::type = 0) const
        {
            rng.sort();
        }

        template< class Result, class Range >
        void call(Range& rng,
            typename disable_if<apple::has_sort<Range> >::type = 0) const
        {
            std::sort(boost::begin(rng), boost::end(rng));
        }
    };

    PSTADE_CONSTANT(sort, (op_sort))


    // stable_sort

    PSTADE_OVEN_DETAIL_FORWARD(stable_sort, std::stable_sort, (boost::mpl::identity<void>), (0)(1))


    // partial_sort

#define PSTADE_partial_sort_form(Xxx, ResultFun) \
    \
    struct BOOST_PP_CAT(op_, Xxx) : \
        callable<BOOST_PP_CAT(op_, Xxx)> \
    { \
        template< class Myself, class Range, class A0, class A1 = void > \
        struct apply : \
            ResultFun \
        { }; \
        \
        template< class Result, class Range, class A1 > \
        Result call(Range& rng, typename range_iterator<Range>::type const& a0, A1& a1) const \
        { \
            return std::Xxx(boost::begin(rng), a0, boost::end(rng), a1); \
        } \
        \
        template< class Result, class Range > \
        Result call(Range& rng, typename range_iterator<Range>::type const& a0) const \
        { \
            return std::Xxx(boost::begin(rng), a0, boost::end(rng)); \
        } \
    }; \
    \
    PSTADE_CONSTANT( Xxx, (BOOST_PP_CAT(op_, Xxx)) ) \
    \
/**/

    PSTADE_partial_sort_form(partial_sort, boost::mpl::identity<void>)


    // partial_sort_copy

    PSTADE_OVEN_DETAIL_FORWARD_BINARY(partial_sort_copy, std::partial_sort_copy, (range_iterator<Range2>), (0)(1))


    // nth_element

    PSTADE_partial_sort_form(nth_element, boost::mpl::identity<void>)


    // lower/upper_bound

#define PSTADE_lower_bound_form(Xxx, ResultFun) \
    \
    struct BOOST_PP_CAT(op_, Xxx) : \
        callable<BOOST_PP_CAT(op_, Xxx)> \
    { \
        template< class Myself, class Range, class A0, class A1 = void > \
        struct apply : \
            ResultFun \
        { }; \
        \
        template< class Result, class Range, class A0, class A1 > \
        Result call(Range& rng, A0& a0, A1& a1) const \
        { \
            return std::Xxx(boost::begin(rng), boost::end(rng), a0, a1); \
        } \
        \
        template< class Result, class Range, class A0 > \
        Result call(Range& rng, A0& a0, \
            typename enable_if< apple::BOOST_PP_CAT(has_, Xxx)<Range> >::type = 0) const \
        { \
            return rng.Xxx(a0); \
        } \
        \
        template< class Result, class Range, class A0 > \
        Result call(Range& rng, A0& a0, \
            typename disable_if<apple::BOOST_PP_CAT(has_, Xxx)<Range> >::type = 0) const \
        { \
            return std::Xxx(boost::begin(rng), boost::end(rng), a0); \
        } \
    }; \
    \
    PSTADE_CONSTANT( Xxx, (BOOST_PP_CAT(op_, Xxx)) ) \
    \
/**/

    PSTADE_lower_bound_form(lower_bound, range_iterator<Range>)
    PSTADE_lower_bound_form(upper_bound, range_iterator<Range>)


    // equal_range

    template< class Range >
    struct detail_equal_range_result
    {
        typedef typename range_iterator<Range>::type iter_t;
        typedef std::pair<iter_t, iter_t> type;
    };

    PSTADE_lower_bound_form(equal_range, detail_equal_range_result<Range>)


    // binary_search

    PSTADE_OVEN_DETAIL_FORWARD(binary_search, std::binary_search, (boost::mpl::identity<bool>), (1)(2))


    // inplace_merge

    PSTADE_partial_sort_form(inplace_merge, boost::mpl::identity<void>)


    // Set Algorithms


    // includes

    PSTADE_OVEN_DETAIL_FORWARD_BINARY(includes, std::includes, (boost::mpl::identity<bool>), (0)(1))


    // merge/set_xxx

    PSTADE_OVEN_DETAIL_FORWARD_BINARY(merge,                    std::merge,                    (pass_by_value<A0>), (1)(2))
    PSTADE_OVEN_DETAIL_FORWARD_BINARY(set_union,                std::set_union,                (pass_by_value<A0>), (1)(2))
    PSTADE_OVEN_DETAIL_FORWARD_BINARY(set_intersection,         std::set_intersection,         (pass_by_value<A0>), (1)(2))
    PSTADE_OVEN_DETAIL_FORWARD_BINARY(set_difference,           std::set_difference,           (pass_by_value<A0>), (1)(2))
    PSTADE_OVEN_DETAIL_FORWARD_BINARY(set_symmetric_difference, std::set_symmetric_difference, (pass_by_value<A0>), (1)(2))


    // xxx_heap

    PSTADE_OVEN_DETAIL_FORWARD(push_heap, std::push_heap, (boost::mpl::identity<void>), (0)(1))
    PSTADE_OVEN_DETAIL_FORWARD(pop_heap,  std::pop_heap,  (boost::mpl::identity<void>), (0)(1))
    PSTADE_OVEN_DETAIL_FORWARD(make_heap, std::make_heap, (boost::mpl::identity<void>), (0)(1))
    PSTADE_OVEN_DETAIL_FORWARD(sort_heap, std::sort_heap, (boost::mpl::identity<void>), (0)(1))


    // min/max_element

    PSTADE_OVEN_DETAIL_FORWARD(min_element, std::min_element, (range_iterator<Range>), (0)(1))
    PSTADE_OVEN_DETAIL_FORWARD(max_element, std::max_element, (range_iterator<Range>), (0)(1))


    // lexicographical_compare

    PSTADE_OVEN_DETAIL_FORWARD_BINARY(lexicographical_compare, std::lexicographical_compare, (boost::mpl::identity<bool>), (0)(1))


    // next/prev_permutation

    PSTADE_OVEN_DETAIL_FORWARD(next_permutation, std::next_permutation, (boost::mpl::identity<bool>), (0)(1))
    PSTADE_OVEN_DETAIL_FORWARD(prev_permutation, std::prev_permutation, (boost::mpl::identity<bool>), (0)(1))


} // ADL barrier


} } // namespace pstade::oven


#undef  PSTADE_fill_n_form
#undef  PSTADE_lower_bound_form
#undef  PSTADE_partial_sort_form


#endif
