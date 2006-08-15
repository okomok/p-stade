#ifndef PSTADE_OVEN_TAKE_WHILE_RANGE_HPP
#define PSTADE_OVEN_TAKE_WHILE_RANGE_HPP


// PStade.Oven
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/range/end.hpp>
#include <pstade/egg/decay_function.hpp>
#include <pstade/egg/function.hpp>
#include <pstade/egg/pipable.hpp>
#include "./algorithm.hpp" // find_if
#include "./detail/concept_check.hpp"
#include "./detail/not.hpp"
#include "./lightweight_proxy.hpp"
#include "./sub_range_base.hpp"


namespace pstade { namespace oven {


template< class Range, class Predicate >
struct drop_while_range :
    sub_range_base<Range>::type,
    private lightweight_proxy< drop_while_range<Range, Predicate> >
{
    typedef Range pstade_oven_range_base_type;

private:
    PSTADE_OVEN_DETAIL_REQUIRES(Range, SinglePassRangeConcept);
    typedef typename sub_range_base<Range>::type super_t;

public:
    drop_while_range(Range& rng, Predicate pred) :
        super_t(oven::find_if(rng, detail::not_(pred)), boost::end(rng))
    { }
};


namespace drop_while_range_detail {


    struct baby_generator
    {
        template< class Unused, class Range, class Predicate >
        struct result
        {
            typedef typename egg::decay_function<Predicate>::type pred_t;
            typedef drop_while_range<Range, pred_t> const type;
        };

        template< class Result, class Range, class Predicate >
        Result call(Range& rng, Predicate& pred)
        {
            return Result(rng, pred);
        }
    };


} // namespace drop_while_range_detail


PSTADE_EGG_FUNCTION(make_drop_while_range, drop_while_range_detail::baby_generator)
PSTADE_EGG_PIPABLE(dropped_while, drop_while_range_detail::baby_generator)


} } // namespace pstade::oven


#endif
