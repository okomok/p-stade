#ifndef PSTADE_OVEN_TAKE_WHILE_RANGE_HPP
#define PSTADE_OVEN_TAKE_WHILE_RANGE_HPP


// PStade.Oven
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// Note:
//
// could be implemented by using 'apply_range'.


#include <boost/range/begin.hpp>
#include <boost/type_traits/remove_cv.hpp>
#include <pstade/egg/function.hpp>
#include "./algorithm.hpp" // find_if
#include "./detail/concept_check.hpp"
#include "./detail/not.hpp"
#include "./is_lightweight_proxy.hpp"
#include "./range_adaptor.hpp"
#include "./sub_range_base_type.hpp"


namespace pstade { namespace oven {


template< class ForwardRange, class Predicate >
struct take_while_range :
    sub_range_base<ForwardRange>::type
{
private:
    PSTADE_OVEN_DETAIL_REQUIRES(ForwardRange, ForwardRangeConcept);
    typedef typename sub_range_base<ForwardRange>::type super_t;

public:
    take_while_range(ForwardRange& rng, Predicate pred) :
        super_t(boost::begin(rng), oven::find_if(rng, detail::not_(pred)))
    { }
};


namespace take_while_range_detail {


    struct baby_generator
    {
        template< class Unused, class ForwardRange, class Predicate >
        struct result
        {
            typedef typename boost::remove_cv<Predicate>::type pred_t;
            typedef take_while_range<ForwardRange, pred_t> const type;
        };

        template< class Result, class ForwardRange, class Predicate >
        Result call(ForwardRange& rng, Predicate pred)
        {
            return Result(rng, pred);
        }
    };


} // namespace take_while_range_detail


PSTADE_EGG_FUNCTION(make_take_while_range, take_while_range_detail::baby_generator)
PSTADE_OVEN_RANGE_ADAPTOR(taken_while, take_while_range_detail::baby_generator)


} } // namespace pstade::oven


PSTADE_OVEN_IS_LIGHTWEIGHT_PROXY_TEMPLATE(pstade::oven::take_while_range, 2)


#endif
