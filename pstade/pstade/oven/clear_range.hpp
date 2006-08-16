#ifndef PSTADE_OVEN_CLEAR_RANGE_HPP
#define PSTADE_OVEN_CLEAR_RANGE_HPP


// PStade.Oven
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/range/end.hpp>
#include <pstade/egg/function.hpp>
#include <pstade/egg/pipable.hpp>
#include "./as_lightweight_proxy.hpp"
#include "./detail/concept_check.hpp"
#include "./sub_range_base.hpp"


namespace pstade { namespace oven {


template< class Range >
struct clear_range :
    sub_range_base<Range>::type,
    private as_lightweight_proxy< clear_range<Range> >
{
    typedef Range pstade_oven_range_base_type;

private:
    PSTADE_OVEN_DETAIL_REQUIRES(Range, SinglePassRangeConcept);
    typedef typename sub_range_base<Range>::type super_t;

public:
    explicit clear_range(Range& rng) :
        super_t(boost::end(rng), boost::end(rng))
    { }
};


namespace clear_range_detail {


    struct baby_generator
    {
        template< class Unused, class Range >
        struct result
        {
            typedef clear_range<Range> const type;
        };

        template< class Result, class Range>
        Result call(Range& rng)
        {
            return Result(rng);
        }
    };


} // namespace clear_range_detail


PSTADE_EGG_FUNCTION(make_clear_range, clear_range_detail::baby_generator)
PSTADE_EGG_PIPABLE(cleared, clear_range_detail::baby_generator)


} } // namespace pstade::oven


#endif
