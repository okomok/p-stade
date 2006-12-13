#ifndef PSTADE_OVEN_APPLY_RANGE_HPP
#define PSTADE_OVEN_APPLY_RANGE_HPP


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// Note:
//
// Will be cute with the upcoming Boost.Phoenix2.


#include <boost/range/end.hpp>
#include <pstade/callable.hpp>
#include <pstade/constant.hpp>
#include <pstade/pass_by.hpp>
#include <pstade/pipable.hpp>
#include "./as_lightweight_proxy.hpp"
#include "./concepts.hpp"
#include "./sub_range_base.hpp"


namespace pstade { namespace oven {


template< class Range >
struct apply_range :
    sub_range_base<Range>::type,
    private as_lightweight_proxy< apply_range<Range> >
{
    PSTADE_CONCEPT_ASSERT((SinglePass<Range>));

private:
    typedef typename sub_range_base<Range>::type super_t;
    typedef typename super_t::iterator iter_t;

public:
    template< class BeginFun, class EndFun >
    apply_range(Range& rng, BeginFun bfun, EndFun efun) :
        super_t(bfun(rng), efun(rng))
    { }

    template< class RangeFun >
    apply_range(Range& rng, RangeFun fun) :
        super_t(fun(rng))
    { }

    typedef Range pstade_oven_range_base_type;
};


struct op_make_apply_range :
    callable<op_make_apply_range>
{
    template< class Myself, class Range, class BeginOrRangeFun, class EndFun = void >
    struct apply
    {
        typedef apply_range<Range> const type;
    };

    template< class Result, class Range, class BeginFun, class EndFun >
    Result call(Range& rng, BeginFun& bfun, EndFun& efun) const
    {
        return Result(rng, bfun, efun);
    }

    template< class Result, class Range, class RangeFun >
    Result call(Range& rng, RangeFun& fun) const
    {
        return Result(rng, fun);
    }
};


PSTADE_CONSTANT(make_apply_range, (op_make_apply_range))
PSTADE_PIPABLE(applied, (op_make_apply_range))


} } // namespace pstade::oven


// for Boost.Phoenix2
//
#if defined(PSTADE_OVEN_USING_PHOENIX_V2)

    #include <boost/spirit/phoenix/core/argument.hpp>
    #include <pstade/constant.hpp>

    namespace pstade { namespace oven {

    PSTADE_CONSTANT(rng1, (boost::phoenix::actor< boost::phoenix::argument<0> >))

    } } // namespace pstade::oven

#endif


#endif
