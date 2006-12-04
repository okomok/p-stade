#ifndef PSTADE_OVEN_DROP_RANGE_HPP
#define PSTADE_OVEN_DROP_RANGE_HPP


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/range/end.hpp>
#include <pstade/egg/function.hpp>
#include <pstade/pipable.hpp>
#include "./as_lightweight_proxy.hpp"
#include "./concepts.hpp"
#include "./detail/debug_in_distance.hpp"
#include "./detail/next_prior.hpp" // next
#include "./sub_range_base.hpp"


namespace pstade { namespace oven {


template< class Range >
struct drop_range :
    sub_range_base<Range>::type,
    private as_lightweight_proxy< drop_range<Range> >
{
    PSTADE_CONCEPT_ASSERT((SinglePass<Range>));

private:
    typedef typename sub_range_base<Range>::type super_t;

public:
    template< class Difference >
    drop_range(Range& rng, Difference d) :
        super_t(detail::next(boost::begin(rng), d), boost::end(rng))
    {
        BOOST_ASSERT(detail::debug_in_distance(d, rng));
    }

    typedef Range pstade_oven_range_base_type;
};


namespace drop_range_detail {


    struct baby_make
    {
        template< class Myself, class Range, class Difference = void >
        struct apply
        {
            typedef drop_range<Range> const type;
        };

        template< class Result, class Range, class Difference >
        Result call(Range& rng, Difference d) const
        {
            return Result(rng, d);
        }
    };


} // namespace drop_range_detail


PSTADE_EGG_FUNCTION(make_drop_range, drop_range_detail::baby_make)
PSTADE_PIPABLE(dropped, make_drop_range_fun)


} } // namespace pstade::oven


#endif
