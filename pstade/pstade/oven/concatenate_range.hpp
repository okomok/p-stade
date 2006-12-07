#ifndef PSTADE_OVEN_CONCATENATE_RANGE_HPP
#define PSTADE_OVEN_CONCATENATE_RANGE_HPP


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>
#include <pstade/egg/function.hpp>
#include <pstade/pipable.hpp>
#include "./as_lightweight_proxy.hpp"
#include "./concatenate_iterator.hpp"
#include "./concepts.hpp"
#include "./iter_range.hpp"
#include "./range_iterator.hpp"
#include "./range_value.hpp"


namespace pstade { namespace oven {


namespace concatenate_range_detail {


    template< class SegmentRange >
    struct super_ :
        iter_range<
            concatenate_iterator<
                typename range_iterator<SegmentRange>::type
            >
        >
    { };


} // namespace concatenate_range_detail


template< class SegmentRange >
struct concatenate_range :
    concatenate_range_detail::super_<SegmentRange>::type,
    private as_lightweight_proxy< concatenate_range<SegmentRange> >
{
    PSTADE_CONCEPT_ASSERT((SinglePass<SegmentRange>));
    PSTADE_CONCEPT_ASSERT((SinglePass<typename range_value<SegmentRange>::type>));

private:
    typedef typename concatenate_range_detail::super_<SegmentRange>::type super_t;
    typedef typename super_t::iterator iter_t;

public:
    explicit concatenate_range(SegmentRange& rngs) :
        super_t(
            iter_t(boost::begin(rngs), boost::end(rngs)),
            iter_t(boost::end(rngs),   boost::end(rngs))
        )
    { }

    typedef SegmentRange pstade_oven_range_base_type;
};


namespace concatenate_range_detail {


    struct baby_make
    {
        template< class Myself, class SegmentRange >
        struct apply
        {
            typedef concatenate_range<SegmentRange> const type;
        };

        template< class Result, class SegmentRange >
        Result call(SegmentRange& rngs) const
        {
            return Result(rngs);
        }
    };


} // namespace concatenate_range_detail


PSTADE_EGG_FUNCTION(make_concatenate_range, concatenate_range_detail::baby_make)
PSTADE_PIPABLE(concatenated, op_make_concatenate_range)


} } // namespace pstade::oven


#endif
