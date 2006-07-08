#ifndef PSTADE_OVEN_TAKE_RANGE_HPP
#define PSTADE_OVEN_TAKE_RANGE_HPP


// PStade.Oven
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/range/begin.hpp>
#include <boost/range/difference_type.hpp>
#include <pstade/egg/function.hpp>
#include "./detail/begin_advance.hpp"
#include "./is_lightweight_proxy.hpp"
#include "./range_adaptor.hpp"
#include "./sub_range_base_type.hpp"


namespace pstade { namespace oven {


template< class ForwardRange >
struct take_range :
    sub_range_base<ForwardRange>::type
{
private:
    typedef typename sub_range_base<ForwardRange>::type super_t;
    typedef typename boost::range_difference<ForwardRange>::type diff_t;

public:
    take_range(ForwardRange& rng, diff_t d) :
        super_t(boost::begin(rng), detail::begin_advance(rng, d))
    { }
};


namespace take_range_detail {


    struct baby_generator
    {
        template< class ForwardRange, class Difference >
        struct result
        {
            typedef take_range<ForwardRange> const type;
        };

        template< class Result, class ForwardRange, class Difference >
        Result call(ForwardRange& rng, Difference d)
        {
            return Result(rng, d);
        }
    };


} // namespace take_range_detail


PSTADE_EGG_FUNCTION(make_take_range, take_range_detail::baby_generator)
PSTADE_OVEN_RANGE_ADAPTOR(taken, take_range_detail::baby_generator)


} } // namespace pstade::oven


PSTADE_OVEN_IS_LIGHTWEIGHT_PROXY_TEMPLATE(pstade::oven::take_range, 1)


#endif
