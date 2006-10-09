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
#include <pstade/egg/function.hpp>
#include <pstade/egg/pipable.hpp>
#include <pstade/pass_by.hpp>
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


namespace apply_range_detail {


    struct baby_make
    {
        template< class Myself, class Range, class BeginOrRangeFun, class EndFun = void >
        struct apply
        {
            typedef apply_range<Range> const type;
        };

        template< class Result, class Range, class BeginFun, class EndFun >
        Result call(Range& rng, BeginFun& bfun, EndFun& efun)
        {
            return Result(rng, bfun, efun);
        }

        template< class Result, class Range, class RangeFun >
        Result call(Range& rng, RangeFun& fun)
        {
            return Result(rng, fun);
        }
    };


} // namespace apply_range_detail


PSTADE_EGG_FUNCTION(make_apply_range, apply_range_detail::baby_make)
PSTADE_EGG_PIPABLE(applied, apply_range_detail::baby_make)


} } // namespace pstade::oven


// for Boost.Phoenix2
//
#if defined(PSTADE_OVEN_USING_PHOENIX_V2)

    #include <boost/spirit/phoenix/core/argument.hpp>
    #include <pstade/instance.hpp>

    namespace pstade { namespace oven {

    PSTADE_INSTANCE(boost::phoenix::actor< boost::phoenix::argument<0> > const, rng1, value)

    } } // namespace pstade::oven

#endif


#endif
