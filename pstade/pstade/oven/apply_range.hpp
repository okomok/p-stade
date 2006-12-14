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
#include <pstade/object_generator.hpp>
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
    typedef apply_range type;

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


PSTADE_OBJECT_GENERATOR(make_apply_range,
    (apply_range< deduce_to_qualified<from_1> >) const)
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
