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
// could be implemented by using 'apply_range'.


#include <boost/range/begin.hpp>
#include <pstade/egg/by_value.hpp>
#include <pstade/egg/function.hpp>
#include <pstade/egg/pipable.hpp>
#include "./algorithm.hpp" // find_if
#include "./as_lightweight_proxy.hpp"
#include "./detail/concept_check.hpp"
#include "./detail/not.hpp"
#include "./sub_range_base.hpp"


namespace pstade { namespace oven {


template< class ForwardRange, class Predicate >
struct take_while_range :
    sub_range_base<ForwardRange>::type,
    private as_lightweight_proxy< take_while_range<ForwardRange, Predicate> >
{
    typedef ForwardRange pstade_oven_range_base_type;

private:
    PSTADE_OVEN_DETAIL_REQUIRES(ForwardRange, ForwardRangeConcept);
    typedef typename sub_range_base<ForwardRange>::type super_t;

public:
    take_while_range(ForwardRange& rng, Predicate const& pred) :
        super_t(boost::begin(rng), oven::find_if(rng, detail::not_(pred)))
    { }
};


namespace take_while_range_detail {


    struct baby_make
    {
        template< class Unused, class ForwardRange, class Predicate >
        struct result
        {
            typedef typename egg::by_value<Predicate>::type pred_t;
            typedef take_while_range<ForwardRange, pred_t> const type;
        };

        template< class Result, class ForwardRange, class Predicate >
        Result call(ForwardRange& rng, Predicate& pred)
        {
            return Result(rng, pred);
        }
    };


} // namespace take_while_range_detail


PSTADE_EGG_FUNCTION(make_take_while_range, take_while_range_detail::baby_make)
PSTADE_EGG_PIPABLE(taken_while, take_while_range_detail::baby_make)


} } // namespace pstade::oven


#endif
