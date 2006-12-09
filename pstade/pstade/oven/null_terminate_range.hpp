#ifndef PSTADE_OVEN_NULL_TERMINATE_RANGE_HPP
#define PSTADE_OVEN_NULL_TERMINATE_RANGE_HPP


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <algorithm> // find
#include <boost/assert.hpp>
#include <boost/range/begin.hpp>
#include <boost/range/empty.hpp>
#include <boost/range/end.hpp>
#include <boost/utility/result_of.hpp>
#include <pstade/const.hpp>
#include <pstade/constant.hpp>
#include <pstade/callable.hpp>
#include <pstade/functional.hpp> // not_, is_zero
#include <pstade/pipable.hpp>
#include <pstade/constant.hpp>
#include "./as_lightweight_proxy.hpp"
#include "./concepts.hpp"
#include "./range_iterator.hpp"
#include "./take_while_range.hpp"


namespace pstade { namespace oven {


template< class Range >
PSTADE_CONCEPT_WHERE(
    ((Forward<Range>)), // ((Readable_const<Range>)),
(bool)) is_null_terminated(Range const& rng)
{
    typedef typename range_iterator<PSTADE_CONST(Range)>::type iter_t;

    iter_t first = boost::begin(rng);
    iter_t last = boost::end(rng);
    iter_t it = std::find(first, last, 0);

    return it != last;
}


template< class Range > inline
void null_terminate(Range& rng)
{
    BOOST_ASSERT(!boost::empty(rng));
    *boost::begin(rng) = 0;
}


namespace null_terminate_range_detail {


    template< class Range >
    struct super_
    {
        typedef typename boost::result_of<pstade::op_not_(op_is_zero const&)>::type pred_t;
        typedef take_while_range<Range, pred_t> type;
    };


} // namespace null_terminate_range_detail



template< class Range >
struct null_terminate_range :
    null_terminate_range_detail::super_<Range>::type,
    private as_lightweight_proxy< null_terminate_range<Range> >
{
    PSTADE_CONCEPT_ASSERT((Forward<Range>));
    // PSTADE_CONCEPT_ASSERT((Readable<Range>));

private:
    typedef typename null_terminate_range_detail::super_<Range>::type super_t;

public:
    explicit null_terminate_range(Range& rng) :
        super_t(rng, pstade::not_(is_zero))
    {
        BOOST_ASSERT(oven::is_null_terminated(rng));
    }
};


struct op_make_null_terminate_range :
    callable<op_make_null_terminate_range>
{
    template< class Myself, class Range >
    struct apply
    {
        typedef null_terminate_range<Range> const type;
    };

    template< class Result, class Range >
    Result call(Range& rng) const
    {
        return Result(rng);
    }
};


PSTADE_CONSTANT(make_null_terminate_range, op_make_null_terminate_range)
PSTADE_PIPABLE(null_terminated, op_make_null_terminate_range)


} } // namespace pstade::oven


#endif
