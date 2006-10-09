#ifndef PSTADE_OVEN_POP_RANGE_HPP
#define PSTADE_OVEN_POP_RANGE_HPP


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/assert.hpp>
#include <boost/next_prior.hpp>
#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>
#include <pstade/egg/function.hpp>
#include <pstade/egg/pipable.hpp>
#include "./as_lightweight_proxy.hpp"
#include "./concepts.hpp"
#include "./distance.hpp"
#include "./sub_range_base.hpp"


namespace pstade { namespace oven {


template< class Range >
struct pop_range :
    sub_range_base<Range>::type,
    private as_lightweight_proxy< pop_range<Range> >
{
    PSTADE_CONCEPT_ASSERT((Bidirectional<Range>));

private:
    typedef typename sub_range_base<Range>::type super_t;

public:
    template< class Difference >
    pop_range(Range& rng, Difference front, Difference back) :
        super_t(boost::next(boost::begin(rng), front), boost::prior(boost::end(rng), back))
    {
        BOOST_ASSERT(0 <= front && 0 <= back);
        BOOST_ASSERT(front + back <= oven::distance(rng));
    }

    typedef Range pstade_oven_range_base_type;
};


namespace pop_range_detail {


    struct baby_make
    {
        template< class Myself, class Range, class DifferenceF, class DifferenceB >
        struct apply
        {
            typedef pop_range<Range> const type;
        };

        template< class Result, class Range, class DifferenceF, class DifferenceB >
        Result call(Range& rng, DifferenceF front, DifferenceB back)
        {
            return Result(rng, front, back);
        }
    };


} // namespace pop_range_detail


PSTADE_EGG_FUNCTION(make_pop_range, pop_range_detail::baby_make)
PSTADE_EGG_PIPABLE(popped, pop_range_detail::baby_make)


} } // namespace pstade::oven


#endif
