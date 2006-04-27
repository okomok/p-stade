#ifndef PSTADE_OVEN_DIRECT_RANGE_HPP
#define PSTADE_OVEN_DIRECT_RANGE_HPP


// PStade.Oven
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>
#include <boost/range/result_iterator.hpp>
#include <pstade/egg/function.hpp>
#include "./counting_range.hpp"
#include "./is_lightweight_proxy.hpp"
#include "./range_adaptor.hpp"


namespace pstade { namespace oven {


namespace direct_range_detail {


    template< class Range >
    struct super_
    {
        typedef typename boost::range_result_iterator<Range>::type iter_t;
        typedef counting_range<iter_t> type;
    };


} // namespace direct_range_detail


template< class Range >
struct direct_range :
    direct_range_detail::super_<Range>::type
{
private:
    typedef typename direct_range_detail::super_<Range>::type super_t;

public:
    template< class Range_ >
    explicit direct_range(Range_& rng) :
        super_t(boost::begin(rng), boost::end(rng))
    { }
};


namespace direct_range_detail {


    struct baby_generator
    {
        template< class Range >
        struct apply
        {
            typedef const direct_range<Range> type;
        };

        template< class Result, class Range >
        Result call(Range& rng)
        {
            return Result(rng);
        }
    };


} // namespace direct_range_detail



PSTADE_EGG_FUNCTION(make_direct_range, direct_range_detail::baby_generator)
PSTADE_OVEN_RANGE_ADAPTOR(directed, direct_range_detail::baby_generator)


} } // namespace pstade::oven


PSTADE_OVEN_IS_LIGHTWEIGHT_PROXY_TEMPLATE(pstade::oven::direct_range, 1)


#endif
