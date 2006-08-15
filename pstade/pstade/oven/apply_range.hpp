#ifndef PSTADE_OVEN_APPLY_RANGE_HPP
#define PSTADE_OVEN_APPLY_RANGE_HPP


// PStade.Oven
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// Note:
//
// Will be cute with the upcoming Boost.Phoenix-v2.


#include <pstade/egg/decay_function.hpp>
#include <pstade/egg/function.hpp>
#include <pstade/egg/pipable.hpp>
#include "./begin_end.hpp"
#include "./detail/concept_check.hpp"
#include "./lightweight_proxy.hpp"
#include "./sub_range_base.hpp"


namespace pstade { namespace oven {


template<
    class Range,
    class BeginFun,
    class EndFun = end_fun
>
struct apply_range :
    sub_range_base<Range>::type,
    private lightweight_proxy< apply_range<Range, BeginFun, EndFun> >
{
    typedef Range pstade_oven_range_base_type;

private:
    PSTADE_OVEN_DETAIL_REQUIRES(Range, SinglePassRangeConcept);
    typedef typename sub_range_base<Range>::type super_t;
    typedef typename super_t::iterator iter_t;

public:
    // Workaround:
    // The weird VC++ needs 'oven::'.
    apply_range(Range& rng, BeginFun bfun, EndFun efun = oven::end) :
        super_t(bfun(rng), efun(rng))
    { }
};


namespace apply_range_detail {


    struct baby_generator
    {
        template< class Unused, class Range, class BeginFun, class EndFun = end_fun >
        struct result
        {
            typedef typename egg::decay_function<BeginFun>::type bfun_t;
            typedef typename egg::decay_function<EndFun>::type efun_t;
            typedef apply_range<Range, bfun_t, efun_t> const type;
        };

        template< class Result, class Range, class BeginFun, class EndFun >
        Result call(Range& rng, BeginFun& bfun, EndFun& efun)
        {
            return Result(rng, bfun, efun);
        }

        template< class Result, class Range, class BeginFun >
        Result call(Range& rng, BeginFun& bfun)
        {
            return Result(rng, bfun);
        }
    };


} // namespace apply_range_detail


PSTADE_EGG_FUNCTION(make_apply_range, apply_range_detail::baby_generator)
PSTADE_EGG_PIPABLE(applied, apply_range_detail::baby_generator)


} } // namespace pstade::oven


// for Boost.Phoenix-v2
//
#if defined(PSTADE_OVEN_USING_PHOENIX_V2)

    #include <boost/spirit/phoenix/core/argument.hpp>
    #include <pstade/instance.hpp>

    namespace pstade { namespace oven {

    PSTADE_INSTANCE(boost::phoenix::actor< boost::phoenix::argument<0> > const, rng1, value)

    } } // namespace pstade::oven

#endif


#endif
