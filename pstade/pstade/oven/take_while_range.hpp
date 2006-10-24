#ifndef PSTADE_OVEN_TAKE_WHILE_RANGE_HPP
#define PSTADE_OVEN_TAKE_WHILE_RANGE_HPP


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// Note:
//
// This range follows the strategy of 'boost::filter_iterator'.
// See his constructor, which is not really lazy.
// Though <boost/archive/iterators/head_iterator.hpp> is lazy,
// the dereference has some overhead, which would be avoided by the Range concept.
// 'Boost.RangeLib' has 'break_iterator', but it seems to be redundant.
// It does in effect the same thing as this range.
// Also note that this range could be implemented by using 'apply_range' with Phoenix2.


#include <boost/range/begin.hpp>
#include <pstade/egg/function.hpp>
#include <pstade/egg/pipable.hpp>
#include <pstade/functional.hpp> // not_
#include "./algorithm.hpp" // find_if
#include "./as_lightweight_proxy.hpp"
#include "./concepts.hpp"
#include "./sub_range_base.hpp"


namespace pstade { namespace oven {


template< class Range >
struct take_while_range :
    sub_range_base<Range>::type,
    private as_lightweight_proxy< take_while_range<Range> >
{
    PSTADE_CONCEPT_ASSERT((Forward<Range>));
    // PSTADE_CONCEPT_ASSERT((Readable<Range>));

private:
    typedef typename sub_range_base<Range>::type super_t;

public:
    template< class Predicate >
    take_while_range(Range& rng, Predicate pred) :
        super_t(boost::begin(rng), oven::find_if(rng, pstade::not_(pred)))
    { }

    typedef Range pstade_oven_range_base_type;
};


namespace take_while_range_detail {


    struct baby_make
    {
        template< class Myself, class Range, class Predicate >
        struct apply
        {
            typedef take_while_range<Range> const type;
        };

        template< class Result, class Range, class Predicate >
        Result call(Range& rng, Predicate& pred)
        {
            return Result(rng, pred);
        }
    };


} // namespace take_while_range_detail


PSTADE_EGG_FUNCTION(make_take_while_range, take_while_range_detail::baby_make)
PSTADE_EGG_PIPABLE(taken_while, take_while_range_detail::baby_make)


} } // namespace pstade::oven


#endif
