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
#include <pstade/unparenthesize.hpp>
#include "./range_difference.hpp"
#include "./range_iterator.hpp"


namespace pstade { namespace oven {


PSTADE_ADL_BARRIER(algorithm) {


    // Non-Modifying Sequence Operations


    // for_each

#define PSTADE_for_each_form(Xxx, ResultFun) \
    \
    struct BOOST_PP_CAT(op_, Xxx) : \
        callable<BOOST_PP_CAT(op_, Xxx)> \
    { \
        template< class Myself, class Range, class A0 > \
        struct apply : \
            ResultFun \
        { }; \
        \
        template< class Result, class Range, class A0 > \
        Result call(Range& rng, A0& a0) const \
        { \
            return std::Xxx(boost::begin(rng), boost::end(rng), a0); \
        } \
    }; \
    \
    PSTADE_CONSTANT( Xxx, (BOOST_PP_CAT(op_, Xxx)) ) \
    \
/**/

    PSTADE_for_each_form(for_each, pass_by_value<A0>)


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

    PSTADE_for_each_form(find_if, range_iterator<Range>)


    // find_end/first_of

#define PSTADE_find_end_form(Xxx, ResultFun) \
    \
    struct BOOST_PP_CAT(op_, Xxx) : \
        callable<BOOST_PP_CAT(op_, Xxx)> \
    { \
        template< class Myself, class Range1, class Range2, class A0 = void > \
        struct apply : \
            ResultFun \
        { }; \
        \
        template< class Result, class Range1, class Range2, class A0 > \
        Result call(Range1& rng1, Range2& rng2, A0& a0) const \
        { \
            return std::Xxx( \
                boost::begin(rng1), boost::end(rng1), \
                boost::begin(rng2), boost::end(rng2), \
                a0 \
            ); \
        } \
        \
        template< class Result, class Range1, class Range2 > \
        Result call(Range1& rng1, Range2& rng2) const \
        { \
            return std::Xxx( \
                boost::begin(rng1), boost::end(rng1), \
                boost::begin(rng2), boost::end(rng2) \
            ); \
        } \
    }; \
    \
    PSTADE_CONSTANT(Xxx, (BOOST_PP_CAT(op_, Xxx)) )
    \
/**/

    PSTADE_find_end_form(find_end, range_iterator<Range1>)
    PSTADE_find_end_form(find_first_of, range_iterator<Range1>)


    // adjacent_find

#define PSTADE_adjacent_find_form(Xxx, ResultFun) \
    \
    struct BOOST_PP_CAT(op_, Xxx) : \
        callable<BOOST_PP_CAT(op_, Xxx)> \
    { \
        template< class Myself, class Range, class A0 = void > \
        struct apply : \
            ResultFun \
        { }; \
        \
        template< class Result, class Range, class A0 > \
        Result call(Range& rng, A0& a0) const \
        { \
            return std::Xxx(boost::begin(rng), boost::end(rng), a0); \
        } \
        template< class Result, class Range > \
        Result call(Range& rng) const \
        { \
            return std::Xxx(boost::begin(rng), boost::end(rng)); \
        } \
    }; \
    \
    PSTADE_CONSTANT( Xxx, (BOOST_PP_CAT(op_, Xxx)) ) \
    \
/**/

    PSTADE_adjacent_find_form(adjacent_find, range_iterator<Range>)


    // count/count_if

    PSTADE_for_each_form(count, range_difference<Range>)
    PSTADE_for_each_form(count_if, range_difference<Range>)


    // mismatch

#define PSTADE_mismatch_form(Xxx, ResultFun) \
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
        Result call(Range& rng, A0& a1) const \
        { \
            return std::Xxx(boost::begin(rng), boost::end(rng), a1); \
        } \
    }; \
    \
    PSTADE_CONSTANT( Xxx, (BOOST_PP_CAT(op_, Xxx)) ) \
    \
/**/

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

    PSTADE_mismatch_form(mismatch, PSTADE_UNPARENTHESIZE((detail_mismatch_result<Range, A0>)))


    // equal

    PSTADE_mismatch_form(equal, boost::mpl::identity<bool>)


    // search

    PSTADE_find_end_form(search, range_iterator<Range1>)


    // Modifying Sequence Operations


    // copy/copy_backward

    PSTADE_for_each_form(copy, pass_by_value<A0>)
    PSTADE_for_each_form(copy_backward, pass_by_value<A0>)


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


    // replace/replace_if

#define PSTADE_replace_form(Xxx, ResultFun) \
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
            return std::Xxx(boost::begin(rng), boost::end(rng), a0, a1); \
        } \
    }; \
    \
    PSTADE_CONSTANT( Xxx, (BOOST_PP_CAT(op_, Xxx)) )
    \
/**/

    PSTADE_replace_form(replace, boost::mpl::identity<void>)
    PSTADE_replace_form(replace_if, boost::mpl::identity<void>)


    // replace_copy/replace_copy_if

#define PSTADE_replace_copy_form(Xxx, ResultFun) \
    \
    struct BOOST_PP_CAT(op_, Xxx) : \
        callable<BOOST_PP_CAT(op_, Xxx)> \
    { \
        template< class Myself, class Range, class A0, class A1, class A2 > \
        struct apply : \
            ResultFun \
        { }; \
        \
        template< class Result, class Range, class A0, class A1, class A2 > \
        Result call(Range& rng, A0& a0, A1& a1, A2& a2) const \
        { \
            return std::Xxx(boost::begin(rng), boost::end(rng), a0, a1, a2); \
        } \
    }; \
    \
    PSTADE_CONSTANT( Xxx, (BOOST_PP_CAT(op_, Xxx)) ) \
    \
/**/

    PSTADE_replace_copy_form(replace_copy, pass_by_value<A0>)
    PSTADE_replace_copy_form(replace_copy_if, pass_by_value<A0>)


    // fill

    PSTADE_for_each_form(fill, boost::mpl::identity<void>)


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

    PSTADE_for_each_form(generate, boost::mpl::identity<void>)


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


    // remove_copy/remove_copy_if

    PSTADE_replace_form(remove_copy, pass_by_value<A0>)
    PSTADE_replace_form(remove_copy_if, pass_by_value<A0>)


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

    PSTADE_mismatch_form(unique_copy, pass_by_value<A0>)


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

    PSTADE_for_each_form(reverse_copy, pass_by_value<A0>)


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

    PSTADE_adjacent_find_form(random_shuffle, boost::mpl::identity<void>)


    // partition/stable_partition

    PSTADE_for_each_form(partition, range_iterator<Range>)
    PSTADE_for_each_form(stable_partition, range_iterator<Range>)


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

    PSTADE_adjacent_find_form(stable_sort, boost::mpl::identity<void>)


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

    PSTADE_find_end_form(partial_sort_copy, range_iterator<Range2>)


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

    PSTADE_mismatch_form(binary_search, boost::mpl::identity<bool>)


    // inplace_merge

    PSTADE_partial_sort_form(inplace_merge, boost::mpl::identity<void>)


    // Set Algorithms


    // includes

    PSTADE_find_end_form(includes, boost::mpl::identity<bool>)


    // merge/set_xxx

#define PSTADE_merge_form(Xxx) \
    \
    struct BOOST_PP_CAT(op_, Xxx) : \
        callable<BOOST_PP_CAT(op_, Xxx)> \
    { \
        template< class Myself, class Range1, class Range2, class OutIter, class Cmp = void > \
        struct apply : \
            pass_by_value<OutIter> \
        { }; \
        \
        template< class Result, class Range1, class Range2, class OutIter, class Cmp > \
        Result call(Range1& rng1, Range2& rng2, OutIter& out, Cmp& cmp) const \
        { \
            return std::Xxx( \
                boost::begin(rng1), boost::end(rng1), \
                boost::begin(rng2), boost::end(rng2), \
                out, cmp \
            ); \
        } \
        \
        template< class Result, class Range1, class Range2, class OutIter > \
        Result call(Range1& rng1, Range2& rng2, OutIter& out) const \
        { \
            return std::Xxx( \
                boost::begin(rng1), boost::end(rng1), \
                boost::begin(rng2), boost::end(rng2), \
                out \
            ); \
        } \
    }; \
    \
    PSTADE_CONSTANT( Xxx, (BOOST_PP_CAT(op_, Xxx)) ) \
    \
/**/

    PSTADE_merge_form(merge)
    PSTADE_merge_form(set_union)
    PSTADE_merge_form(set_intersection)
    PSTADE_merge_form(set_difference)
    PSTADE_merge_form(set_symmetric_difference)


    // xxx_heap

    PSTADE_adjacent_find_form(push_heap, boost::mpl::identity<void>)
    PSTADE_adjacent_find_form(pop_heap,  boost::mpl::identity<void>)
    PSTADE_adjacent_find_form(make_heap, boost::mpl::identity<void>)
    PSTADE_adjacent_find_form(sort_heap, boost::mpl::identity<void>)


    // min_element/max_element

    PSTADE_adjacent_find_form(min_element, range_iterator<Range>)
    PSTADE_adjacent_find_form(max_element, range_iterator<Range>)


    // lexicographical_compare

    PSTADE_find_end_form(lexicographical_compare, boost::mpl::identity<bool>)


    // next/prev_permutation

    PSTADE_adjacent_find_form(next_permutation, boost::mpl::identity<bool>)
    PSTADE_adjacent_find_form(prev_permutation, boost::mpl::identity<bool>)


} // ADL barrier


} } // namespace pstade::oven


#undef  PSTADE_adjacent_find_form
#undef  PSTADE_fill_n_form
#undef  PSTADE_find_end_form
#undef  PSTADE_for_each_form
#undef  PSTADE_lower_bound_form
#undef  PSTADE_merge_form
#undef  PSTADE_mismatch_form
#undef  PSTADE_partial_sort_form
#undef  PSTADE_replace_copy_form
#undef  PSTADE_replace_form


#endif
