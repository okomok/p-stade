#ifndef PSTADE_OVEN_SLICE_RANGE_HPP
#define PSTADE_OVEN_SLICE_RANGE_HPP


// PStade.Oven
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/assert.hpp>
#include <boost/range/difference_type.hpp>
#include <pstade/egg/function.hpp>
#include "./distance.hpp"
#include "./is_lightweight_proxy.hpp"
#include "./range_adaptor.hpp"
#include "./sub_range_base_type.hpp"


namespace pstade { namespace oven {


template< class BidiRange >
struct slice_range :
    sub_range_base<BidiRange>::type
{
private:
    typedef typename sub_range_base<BidiRange>::type super_t;
    typedef typename boost::range_difference<BidiRange>::type diff_t;

public:
    slice_range(BidiRange& rng, diff_t n, diff_t m) :
        super_t(boost::make_iterator_range(rng, n, m))
    {
        BOOST_ASSERT( oven::distance(rng) >= n+m );
    }
};


namespace slice_range_detail {


    struct baby_generator
    {
        template< class BidiRange, class DifferenceN, class DifferenceM >
        struct result
        {
            typedef slice_range<BidiRange> const type;
        };

        template< class Result, class BidiRange, class Difference >
        Result call(BidiRange& rng, Difference n, Difference m)
        {
            return Result(rng, n, m);
        }
    };


} // namespace slice_range_detail


PSTADE_EGG_FUNCTION(make_slice_range, slice_range_detail::baby_generator)
PSTADE_OVEN_RANGE_ADAPTOR(sliced, slice_range_detail::baby_generator)


} } // namespace pstade::oven


PSTADE_OVEN_IS_LIGHTWEIGHT_PROXY_TEMPLATE(pstade::oven::slice_range, 1)


#endif
