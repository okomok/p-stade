#ifndef PSTADE_OVEN_UNIQUE_RANGE_HPP
#define PSTADE_OVEN_UNIQUE_RANGE_HPP


// PStade.Oven
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/egg/function.hpp>
#include "./adjacent_filter_range.hpp"
#include "./detail/not_equal_to.hpp"
#include "./is_lightweight_proxy.hpp"
#include "./range_adaptor.hpp"


namespace pstade { namespace oven {


namespace unique_range_detail {


    template< class ForwardRange >
    struct super_
    {
        typedef adjacent_filter_range<
            ForwardRange,
            detail::not_equal_to_fun
        > type;
    };


} // namespace unique_range_detail


template< class ForwardRange >
struct unique_range :
    unique_range_detail::super_<ForwardRange>::type
{
private:
    typedef typename unique_range_detail::super_<ForwardRange>::type super_t;

public:
    explicit unique_range(ForwardRange& rng) :
        super_t(rng, detail::not_equal_to)
    { }
};


namespace unique_range_detail {


    struct baby_generator
    {
        template< class ForwardRange >
        struct result
        {
            typedef const unique_range<ForwardRange> type;
        };

        template< class Result, class ForwardRange >
        Result call(ForwardRange& rng)
        {
            return Result(rng);
        }
    };


} // namespace unique_range_detail


PSTADE_EGG_FUNCTION(make_unique_range, unique_range_detail::baby_generator)
PSTADE_OVEN_RANGE_ADAPTOR(uniqued, unique_range_detail::baby_generator)


} } // namespace pstade::oven


PSTADE_OVEN_IS_LIGHTWEIGHT_PROXY_TEMPLATE(pstade::oven::unique_range, 1)


#endif
