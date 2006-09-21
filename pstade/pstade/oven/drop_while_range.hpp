#ifndef PSTADE_OVEN_TAKE_WHILE_RANGE_HPP
#define PSTADE_OVEN_TAKE_WHILE_RANGE_HPP


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/range/end.hpp>
#include <pstade/egg/function.hpp>
#include <pstade/egg/pipable.hpp>
#include <pstade/functional.hpp> // not
#include <pstade/pass_by.hpp>
#include "./algorithm.hpp" // find_if
#include "./as_lightweight_proxy.hpp"
#include "./detail/concept_check.hpp"
#include "./sub_range_base.hpp"


namespace pstade { namespace oven {


template< class Range, class Predicate >
struct drop_while_range :
    sub_range_base<Range>::type,
    private as_lightweight_proxy< drop_while_range<Range, Predicate> >
{
    typedef Range pstade_oven_range_base_type;
    typedef Predicate predicate_type;

private:
    PSTADE_OVEN_DETAIL_REQUIRES(Range, SinglePassRangeConcept);
    typedef typename sub_range_base<Range>::type super_t;

public:
    drop_while_range(Range& rng, Predicate const& pred) :
        super_t(oven::find_if(rng, pstade::not_(pred)), boost::end(rng))
    { }
};


namespace drop_while_range_detail {


    struct baby_make
    {
        template< class Unused, class Range, class Predicate >
        struct smile
        {
            typedef typename pass_by_value<Predicate>::type pred_t;
            typedef drop_while_range<Range, pred_t> const type;
        };

        template< class Result, class Range, class Predicate >
        Result call(Range& rng, Predicate& pred)
        {
            return Result(rng, pred);
        }
    };


} // namespace drop_while_range_detail


PSTADE_EGG_FUNCTION(make_drop_while_range, drop_while_range_detail::baby_make)
PSTADE_EGG_PIPABLE(dropped_while, drop_while_range_detail::baby_make)


} } // namespace pstade::oven


#endif
