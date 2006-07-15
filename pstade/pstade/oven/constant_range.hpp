#ifndef PSTADE_OVEN_CONSTANT_RANGE_HPP
#define PSTADE_OVEN_CONSTANT_RANGE_HPP


// PStade.Oven
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/egg/function.hpp>
#include "./detail/concept_check.hpp"
#include "./is_lightweight_proxy.hpp"
#include "./range_adaptor.hpp"
#include "./sub_range_base_type.hpp"


namespace pstade { namespace oven {


template< class IgnoredRange, class Range >
struct constant_range :
    sub_range_base<Range>::type
{
private:
    PSTADE_OVEN_DETAIL_REQUIRES(IgnoredRange, SinglePassRangeConcept);
    PSTADE_OVEN_DETAIL_REQUIRES(Range, SinglePassRangeConcept);
    typedef typename sub_range_base<Range>::type super_t;

public:
    constant_range(IgnoredRange& , Range& rng) :
        super_t(rng)
    { }
};


namespace constant_range_detail {


    struct baby_generator
    {
        template< class Unused, class IgnoredRange, class Range >
        struct result
        {
            typedef constant_range<IgnoredRange, Range> const type;
        };

        template< class Result, class IgnoredRange, class Range>
        Result call(IgnoredRange& _, Range& rng)
        {
            return Result(_, rng);
        }
    };


} // namespace constant_range_detail


PSTADE_EGG_FUNCTION(make_constant_range, constant_range_detail::baby_generator)
PSTADE_OVEN_RANGE_ADAPTOR(constants, constant_range_detail::baby_generator)


} } // namespace pstade::oven


PSTADE_OVEN_IS_LIGHTWEIGHT_PROXY_TEMPLATE(pstade::oven::constant_range, 2)


#endif
