#ifndef PSTADE_OVEN_MERGED_HPP
#define PSTADE_OVEN_MERGED_HPP


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/preprocessor/cat.hpp>
#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>
#include <pstade/callable.hpp>
#include <pstade/constant.hpp>
#include <pstade/functional.hpp> // less
#include <pstade/pipable.hpp>
#include "./concepts.hpp"
#include "./iter_range.hpp"
#include "./merge_iterator.hpp"
#include "./range_iterator.hpp"


namespace pstade { namespace oven {


namespace merged_detail {


    template< class MergeRoutine >
    struct op_make :
        callable< op_make<MergeRoutine> >
    {
        template< class Myself, class Range1, class Range2, class Compare = op_less >
        struct apply
        {
            typedef
                merge_iterator<
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
            // PSTADE_CONCEPT_ASSERT((Readable<Range1>));
            PSTADE_CONCEPT_ASSERT((SinglePass<Range2>));
            // PSTADE_CONCEPT_ASSERT((Readable<Range2>));

            typedef typename Result::iterator iter_t;
            return Result(
                iter_t(boost::begin(rng1), boost::end(rng1), boost::begin(rng2), boost::end(rng2), comp),
                iter_t(boost::end(rng1),   boost::end(rng1), boost::end(rng2),   boost::end(rng2), comp)
            );
        }

        template< class Result, class Range1, class Range2 >
        Result call(Range1& rng1, Range2& rng2) const
        {
            return (*this)(rng1, rng2, less);
        }
    };


} // namespace merged_detail


typedef merged_detail::op_make<merge_iterator_detail::merge_routine> op_make_merged;
PSTADE_CONSTANT(make_merged, (op_make_merged))
PSTADE_PIPABLE(merged, (op_make_merged))


} } // namespace pstade::oven


#define PSTADE_OVEN_DETAIL_MERGE_ADAPTOR(Name, MergeRoutine) \
    struct BOOST_PP_CAT(op_make_, Name) : \
        ::pstade::callable<BOOST_PP_CAT(op_make_, Name)> \
    { \
        template< class Myself, class Range1, class Range2, class Compare = ::pstade::op_less > \
        struct apply \
        { \
            typedef typename \
                ::boost::result_of< \
                    ::pstade::oven::merged_detail::op_make< MergeRoutine >(Range1&, Range2&, Compare&) \
                >::type \
            type; \
        }; \
        \
        template< class Result, class Range1, class Range2, class Compare > \
        Result call(Range1& rng1, Range2& rng2, Compare& comp) const \
        { \
            return ::pstade::oven::merged_detail::op_make< MergeRoutine >()(rng1, rng2, comp); \
        } \
        \
        template< class Result, class Range1, class Range2 > \
        Result call(Range1& rng1, Range2& rng2) const \
        { \
            return (*this)(rng1, rng2, ::pstade::less); \
        } \
    }; \
    \
    PSTADE_CONSTANT(BOOST_PP_CAT(make_, Name), (BOOST_PP_CAT(op_make_, Name))) \
    PSTADE_PIPABLE(Name, (BOOST_PP_CAT(op_make_, Name))) \
/**/


#endif
