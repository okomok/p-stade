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


#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>
#include <pstade/object_generator.hpp>
#include <pstade/pipable.hpp>
#include "./as_lightweight_proxy.hpp"
#include "./concepts.hpp"
#include "./detail/next_prior.hpp" // next
#include "./sub_range_base.hpp"


namespace pstade { namespace oven {


namespace advance_range_detail {


    template< class Super, class Range, class Difference > inline
    Super make(Range& rng, Difference dfirst, Difference dlast)
    {
        BOOST_ASSERT(0 + dfirst <= oven::distance(rng) + dlast);

        return Super(
            detail::next(boost::begin(rng), dfirst),
            detail::next(boost::end(rng), dlast));
    }


} // namespace advance_range_detail


template< class Range >
struct advance_range :
    sub_range_base<Range>::type,
    private as_lightweight_proxy< advance_range<Range> >
{
    PSTADE_CONCEPT_ASSERT((Forward<Range>));
    typedef advance_range type;

private:
    typedef typename sub_range_base<Range>::type super_t;

public:
    template< class Difference >
    advance_range(Range& rng, Difference dfirst, Difference dlast) :
        super_t(advance_range_detail::make<super_t>(rng, dfirst, dlast))
    { }

    template< class Difference >
    advance_range(Range& rng, Difference d) :
        super_t(advance_range_detail::make<super_t>(rng, d, d))
    { }

    typedef Range pstade_oven_range_base_type;
};


PSTADE_OBJECT_GENERATOR(make_advance_range, advance_range< deduce_to_qualified<from_1> > const)
PSTADE_PIPABLE(advanced, op_make_advance_range)


} } // namespace pstade::oven


#endif
