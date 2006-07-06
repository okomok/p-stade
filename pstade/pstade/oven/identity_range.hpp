#ifndef PSTADE_OVEN_IDENTITY_RANGE_HPP
#define PSTADE_OVEN_IDENTITY_RANGE_HPP


// PStade.Oven
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/egg/function.hpp>
#include "./is_lightweight_proxy.hpp"
#include "./range_adaptor.hpp"
#include "./sub_range_base_type.hpp"


namespace pstade { namespace oven {


template< class Range >
struct identity_range :
    sub_range_base<Range>::type
{
private:
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
        template< class Range >
        struct result
        {
            typedef const identity_range<Range> type;
        };

        template< class Result, class Range >
        Result call(Range& rng)
        {
            return Result(rng);
        }
    };


} // namespace identity_range_detail


PSTADE_EGG_FUNCTION(make_identity_range, identity_range_detail::baby_generator)
PSTADE_OVEN_RANGE_ADAPTOR(identities, identity_range_detail::baby_generator)


} } // namespace pstade::oven


PSTADE_OVEN_IS_LIGHTWEIGHT_PROXY_TEMPLATE(pstade::oven::identity_range, 1)


#endif
