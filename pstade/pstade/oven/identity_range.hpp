#ifndef PSTADE_OVEN_IDENTITY_RANGE_HPP
#define PSTADE_OVEN_IDENTITY_RANGE_HPP


// PStade.Oven
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/egg/function.hpp>
#include <pstade/egg/pipeline.hpp>
#include "./detail/concept_check.hpp"
#include "./lightweight_proxy.hpp"
#include "./sub_range_base.hpp"


namespace pstade { namespace oven {


template< class Range >
struct identity_range :
    sub_range_base<Range>::type,
    private lightweight_proxy< identity_range<Range> >
{
    typedef Range pstade_oven_range_base_type;

private:
    PSTADE_OVEN_DETAIL_REQUIRES(Range, SinglePassRangeConcept);
    typedef typename sub_range_base<Range>::type super_t;
    typedef typename super_t::iterator iter_t;

public:
    explicit identity_range(Range& rng) :
        super_t(rng)
    { }
};


namespace identity_range_detail {


    struct baby_generator
    {
        template< class Unused, class Range >
        struct result
        {
            typedef identity_range<Range> const type;
        };

        template< class Result, class Range >
        Result call(Range& rng)
        {
            return Result(rng);
        }
    };


} // namespace identity_range_detail


PSTADE_EGG_FUNCTION(make_identity_range, identity_range_detail::baby_generator)
PSTADE_EGG_PIPELINE(identities,          identity_range_detail::baby_generator)


} } // namespace pstade::oven


#endif
