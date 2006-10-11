#ifndef PSTADE_OVEN_ADVANCE_RANGE_HPP
#define PSTADE_OVEN_ADVANCE_RANGE_HPP


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// Note:
//
// This range had the name 'shift_range',
// which is reserved to "logical shift operation" for someday.
// 'cshift_range'(cyclic shift operation) is also a candidate. 


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
struct advance_range :
    sub_range_base<Range>::type,
    private as_lightweight_proxy< advance_range<Range> >
{
    PSTADE_CONCEPT_ASSERT((Forward<Range>));

private:
    typedef typename sub_range_base<Range>::type super_t;

public:
    template< class Difference >
    advance_range(Range& rng, Difference d) :
        super_t(boost::next(boost::begin(rng), d), boost::next(boost::end(rng), d))
    { }

    typedef Range pstade_oven_range_base_type;
};


namespace advance_range_detail {


    struct baby_make
    {
        template< class Myself, class Range, class Difference >
        struct apply
        {
            typedef advance_range<Range> const type;
        };

        template< class Result, class Range, class Difference >
        Result call(Range& rng, Difference d)
        {
            return Result(rng, d);
        }
    };


} // namespace advance_range_detail


PSTADE_EGG_FUNCTION(make_advance_range, advance_range_detail::baby_make)
PSTADE_EGG_PIPABLE(advanced, advance_range_detail::baby_make)


} } // namespace pstade::oven


#endif
