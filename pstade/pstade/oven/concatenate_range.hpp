#ifndef PSTADE_OVEN_CONCATENATE_RANGE_HPP
#define PSTADE_OVEN_CONCATENATE_RANGE_HPP


// PStade.Oven
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>
#include <boost/range/iterator_range.hpp>
#include <pstade/egg/function.hpp>
#include <pstade/egg/pipable.hpp>
#include "./as_lightweight_proxy.hpp"
#include "./concatenate_iterator.hpp"
#include "./detail/concept_check.hpp"
#include "./range_iterator.hpp"


namespace pstade { namespace oven {


namespace concatenate_range_detail {


    template< class RangeRange >
    struct super_
    {
        typedef boost::iterator_range<
            concatenate_iterator<
                typename range_iterator<RangeRange>::type
            >
        > type;
    };


} // namespace concatenate_range_detail


template< class RangeRange >
struct concatenate_range :
    concatenate_range_detail::super_<RangeRange>::type,
    private as_lightweight_proxy< concatenate_range<RangeRange> >
{
    typedef RangeRange pstade_oven_range_base_type;

private:
    PSTADE_OVEN_DETAIL_REQUIRES(RangeRange, SinglePassRangeConcept);
    typedef typename concatenate_range_detail::super_<RangeRange>::type super_t;
    typedef typename super_t::iterator iter_t;

public:
    explicit concatenate_range(RangeRange& rngs) :
        super_t(
            iter_t(boost::begin(rngs), boost::end(rngs)),
            iter_t(boost::end(rngs),   boost::end(rngs))
        )
    { }
};


namespace concatenate_range_detail {


    struct baby_generator
    {
        template< class Unused, class RangeRange >
        struct result
        {
            typedef concatenate_range<RangeRange> const type;
        };

        template< class Result, class RangeRange >
        Result call(RangeRange& rngs)
        {
            return Result(rngs);
        }
    };


} // namespace concatenate_range_detail


PSTADE_EGG_FUNCTION(make_concatenate_range, concatenate_range_detail::baby_generator)
PSTADE_EGG_PIPABLE(concatenated, concatenate_range_detail::baby_generator)


} } // namespace pstade::oven


#endif
