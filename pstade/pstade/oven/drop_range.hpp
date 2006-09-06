#ifndef PSTADE_OVEN_DROP_RANGE_HPP
#define PSTADE_OVEN_DROP_RANGE_HPP


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/range/end.hpp>
#include <pstade/egg/function.hpp>
#include <pstade/egg/pipable.hpp>
#include "./as_lightweight_proxy.hpp"
#include "./detail/advance_begin.hpp"
#include "./detail/concept_check.hpp"
#include "./range_difference.hpp"
#include "./sub_range_base.hpp"


namespace pstade { namespace oven {


template< class Range >
struct drop_range :
    sub_range_base<Range>::type,
    private as_lightweight_proxy< drop_range<Range> >
{
    typedef Range pstade_oven_range_base_type;

private:
    PSTADE_OVEN_DETAIL_REQUIRES(Range, SinglePassRangeConcept);
    typedef typename sub_range_base<Range>::type super_t;
    typedef typename range_difference<Range>::type diff_t;

public:
    drop_range(Range& rng, diff_t d) :
        super_t(detail::advance_begin(rng, d), boost::end(rng))
    { }
};


namespace drop_range_detail {


    struct baby_generator
    {
        template< class Unused, class Range, class Difference = void >
        struct result
        {
            typedef drop_range<Range> const type;
        };

        template< class Result, class Range, class Difference >
        Result call(Range& rng, Difference d)
        {
            return Result(rng, d);
        }
    };


} // namespace drop_range_detail


PSTADE_EGG_FUNCTION(make_drop_range, drop_range_detail::baby_generator)
PSTADE_EGG_PIPABLE(dropped, drop_range_detail::baby_generator)


} } // namespace pstade::oven


#endif
