#ifndef PSTADE_OVEN_MOVE_RANGE_HPP
#define PSTADE_OVEN_MOVE_RANGE_HPP


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// Pending...
//


// Note:
//
// Is this range is really needed?
// 'transformed(move)' seems enough?


#include <boost/move.hpp>
#include <boost/mpl/if.hpp>
#include <pstade/callable.hpp>
#include <pstade/constant.hpp>
#include <pstade/pipable.hpp>
#include "./as_lightweight_proxy.hpp"
#include "./concepts.hpp"
#include "./range_value.hpp"
#include "./transform_range.hpp"


namespace pstade { namespace oven {


namespace move_range_detail {


    template< class Value >
    struct op_move
    {
        typedef typename boost::mpl::if_<
            boost::is_movable<Value>,
            Value, Value&
        >::type result_type;

        template< class T >
        result_type operator()(T& x) const
        {
            return boost::move(x);
        }
    };


    template< class Range >
    struct super_
    {
        typedef transform_range<
            Range,
            op_move<typename range_value<Range>::type>
        > type;
    };


} // namespace move_range_detail


template< class Range >
struct move_range :
    move_range_detail::super_<Range>::type,
    private as_lightweight_proxy< move_range<Range> >
{
    PSTADE_CONCEPT_ASSERT((SinglePass<Range>));
    PSTADE_CONCEPT_ASSERT((Lvalue<Range>));

private:
    typedef typename move_range_detail::super_<Range>::type super_t;
    typedef typename super_t::function_type fun_t;

public:
    explicit move_range(Range& rng) :
        super_t(rng, fun_t())
    { }
};


struct op_make_move_range :
    callable<op_make_move_range>
{
    template< class Myself, class Range >
    struct apply
    {
        typedef move_range<Range> const type;
    };

    template< class Result, class Range >
    Result call(Range& rng) const
    {
        return Result(rng);
    }
};


PSTADE_CONSTANT(make_move_range, op_make_move_range)
PSTADE_PIPABLE(moved, op_make_move_range)


} } // namespace pstade::oven


#endif
