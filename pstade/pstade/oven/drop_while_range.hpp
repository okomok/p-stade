#ifndef PSTADE_OVEN_DROP_WHILE_RANGE_HPP
#define PSTADE_OVEN_DROP_WHILE_RANGE_HPP


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// Question:
//
// Should this be implemented by 'head_iterator' or something,
// which makes this really lazy?


#include <boost/range/end.hpp>
#include <pstade/egg/function.hpp>
#include <pstade/functional.hpp> // not_
#include <pstade/pipable.hpp>
#include "./algorithm.hpp" // find_if
#include "./as_lightweight_proxy.hpp"
#include "./concepts.hpp"
#include "./sub_range_base.hpp"


namespace pstade { namespace oven {


template< class Range >
struct drop_while_range :
    sub_range_base<Range>::type,
    private as_lightweight_proxy< drop_while_range<Range> >
{
    PSTADE_CONCEPT_ASSERT((SinglePass<Range>));
    // PSTADE_CONCEPT_ASSERT((Readable<Range>));

private:
    typedef typename sub_range_base<Range>::type super_t;

public:
    template< class Predicate >
    drop_while_range(Range& rng, Predicate pred) :
        super_t(oven::find_if(rng, pstade::not_(pred)), boost::end(rng))
    { }

    typedef Range pstade_oven_range_base_type;
};


namespace drop_while_range_detail {


    struct baby_make
    {
        template< class Myself, class Range, class Predicate >
        struct apply
        {
            typedef drop_while_range<Range> const type;
        };

        template< class Result, class Range, class Predicate >
        Result call(Range& rng, Predicate& pred) const
        {
            return Result(rng, pred);
        }
    };


} // namespace drop_while_range_detail


PSTADE_EGG_FUNCTION(make_drop_while_range, drop_while_range_detail::baby_make)
PSTADE_PIPABLE(dropped_while, make_drop_while_range_fun)


} } // namespace pstade::oven


#endif
