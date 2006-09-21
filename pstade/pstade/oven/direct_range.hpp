#ifndef PSTADE_OVEN_DIRECT_RANGE_HPP
#define PSTADE_OVEN_DIRECT_RANGE_HPP


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>
#include <pstade/egg/function.hpp>
#include <pstade/egg/pipable.hpp>
#include "./as_lightweight_proxy.hpp"
#include "./counting_range.hpp"
#include "./detail/concept_check.hpp"
#include "./range_iterator.hpp"


namespace pstade { namespace oven {


namespace direct_range_detail {


    template< class Range >
    struct super_
    {
        typedef typename range_iterator<Range>::type iter_t;
        typedef counting_range<iter_t> type;
    };


} // namespace direct_range_detail


template< class Range >
struct direct_range :
    direct_range_detail::super_<Range>::type,
    private as_lightweight_proxy< direct_range<Range> >
{
    typedef Range pstade_oven_range_base_type;

private:
    PSTADE_OVEN_DETAIL_REQUIRES(Range, SinglePassRangeConcept);
    typedef typename direct_range_detail::super_<Range>::type super_t;

public:
    explicit direct_range(Range& rng) :
        super_t(boost::begin(rng), boost::end(rng))
    { }
};


namespace direct_range_detail {


    struct baby_make
    {
        template< class Unused, class Range >
        struct smile
        {
            typedef direct_range<Range> const type;
        };

        template< class Result, class Range >
        Result call(Range& rng)
        {
            return Result(rng);
        }
    };


} // namespace direct_range_detail



PSTADE_EGG_FUNCTION(make_direct_range, direct_range_detail::baby_make)
PSTADE_EGG_PIPABLE(directed, direct_range_detail::baby_make)


} } // namespace pstade::oven


#endif
