#ifndef PSTADE_OVEN_SHIFT_RANGE_HPP
#define PSTADE_OVEN_SHIFT_RANGE_HPP


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/next_prior.hpp> // next
#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>
#include <pstade/egg/function.hpp>
#include <pstade/egg/pipable.hpp>
#include "./as_lightweight_proxy.hpp"
#include "./concepts.hpp"
#include "./sub_range_base.hpp"


namespace pstade { namespace oven {


template< class Range >
struct shift_range :
    sub_range_base<Range>::type,
    private as_lightweight_proxy< shift_range<Range> >
{
    PSTADE_CONCEPT_ASSERT((Forward<Range>));

private:
    typedef typename sub_range_base<Range>::type super_t;

public:
    template< class Difference >
    shift_range(Range& rng, Difference d) :
        super_t(boost::next(boost::begin(rng), d), boost::next(boost::end(rng), d))
    { }

    typedef Range pstade_oven_range_base_type;
};


namespace shift_range_detail {


    struct baby_make
    {
        template< class Myself, class Range, class Difference >
        struct apply
        {
            typedef shift_range<Range> const type;
        };

        template< class Result, class Range, class Difference >
        Result call(Range& rng, Difference d)
        {
            return Result(rng, d);
        }
    };


} // namespace shift_range_detail


PSTADE_EGG_FUNCTION(make_shift_range, shift_range_detail::baby_make)
PSTADE_EGG_PIPABLE(shifted, shift_range_detail::baby_make)


} } // namespace pstade::oven


#endif
