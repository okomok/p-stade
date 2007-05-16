#ifndef PSTADE_OVEN_REPLICATE_RANGE_HPP
#define PSTADE_OVEN_REPLICATE_RANGE_HPP


// PStade.Oven
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/tuple/tuple.hpp>
#include <pstade/egg/function.hpp>
#include "./is_lightweight_proxy.hpp"
#include "./range_adaptor.hpp"
#include "./zip_range.hpp"


namespace pstade { namespace oven {


namespace replicate_range_detail {


    template< class Range >
    struct super_
    {
        typedef boost::tuples::tuple<Range&, Range&>::type tup_t;
        typedef zip_range<tup_t> type;
    };


} // namespace replicate_range_detail


template< class Range >
struct replicate_range :
    replicate_range_detail::super_<Range>::type
{
private:
    typedef typename replicate_range_detail::super_<Range>::type super_t;

public:
    explicit replicate_range(Range& rng) :
        super_t(boost::tuples::tie(rng, rng))
    { }
};


namespace replicate_range_detail {


    struct baby_generator
    {
        template< class Range >
        struct result
        {
            typedef const replicate_range<Range> type;
        };

        template< class Result, class Range >
        Result call(Range& rng)
        {
            return Result(rng);
        }
    };


} // namespace replicate_range_detail


PSTADE_EGG_FUNCTION(make_replicate_range, replicate_range_detail::baby_generator)
PSTADE_OVEN_RANGE_ADAPTOR(replicated, replicate_range_detail::baby_generator)


} } // namespace pstade::oven


PSTADE_OVEN_IS_LIGHTWEIGHT_PROXY_TEMPLATE(pstade::oven::replicate_range, 1)


#endif
