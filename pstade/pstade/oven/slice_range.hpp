#ifndef PSTADE_OVEN_SLICE_RANGE_HPP
#define PSTADE_OVEN_SLICE_RANGE_HPP


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/assert.hpp>
#include <boost/next_prior.hpp> // next
#include <boost/range/begin.hpp>
#include <pstade/egg/function.hpp>
#include <pstade/egg/pipable.hpp>
#include "./as_lightweight_proxy.hpp"
#include "./concepts.hpp"
#include "./distance.hpp"
#include "./range_iterator.hpp"
#include "./sub_range_base.hpp"


namespace pstade { namespace oven {


namespace slice_range_detail {


    template< class Super, class Range, class Difference >
    Super make(Range& rng, Difference n, Difference m)
    {
        BOOST_ASSERT(0 <= n && n <= m && m <= oven::distance(rng));

        typedef typename range_iterator<Range>::type iter_t;
        iter_t first = boost::next(boost::begin(rng), n);
        return Super(first, boost::next(first, m - n));
    }


} // namespace slice_range_detail


template< class Range >
struct slice_range :
    sub_range_base<Range>::type,
    private as_lightweight_proxy< slice_range<Range> >
{
    PSTADE_CONCEPT_ASSERT((Forward<Range>));

private:
    typedef typename sub_range_base<Range>::type super_t;

public:
    template< class Difference >
    slice_range(Range& rng, Difference n, Difference m) :
        super_t(slice_range_detail::make<super_t>(rng, n, m))
    { }

    typedef Range pstade_oven_range_base_type;
};


namespace slice_range_detail {


    struct baby_make
    {
        template< class Myself, class Range, class DifferenceN, class DifferenceM >
        struct apply
        {
            typedef slice_range<Range> const type;
        };

        template< class Result, class Range, class Difference >
        Result call(Range& rng, Difference n, Difference m)
        {
            return Result(rng, n, m);
        }
    };


} // namespace slice_range_detail


PSTADE_EGG_FUNCTION(make_slice_range, slice_range_detail::baby_make)
PSTADE_EGG_PIPABLE(sliced, slice_range_detail::baby_make)


} } // namespace pstade::oven


#endif
