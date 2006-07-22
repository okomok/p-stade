#ifndef PSTADE_OVEN_ACCUMULATE_RANGE_HPP
#define PSTADE_OVEN_ACCUMULATE_RANGE_HPP


// PStade.Oven
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>
#include <boost/range/iterator_range.hpp>
#include <pstade/egg/decay_function.hpp>
#include <pstade/egg/function.hpp>
#include "./accumulate_iterator.hpp"
#include "./detail/concept_check.hpp"
#include "./detail/plus.hpp"
#include "./is_lightweight_proxy.hpp"
#include "./range_adaptor.hpp"
#include "./range_iterator.hpp"
#include "./range_value.hpp"


namespace pstade { namespace oven {


namespace accumulate_range_detail {


    template< class Range, class BinaryFun >
    struct super_
    {
        typedef boost::iterator_range<
            accumulate_iterator<
                typename range_iterator<Range>::type,
                BinaryFun
            >
        > type;
    };


} // namespace accumulate_range_detail


template< class Range, class BinaryFun = detail::plus_fun >
struct accumulate_range :
    accumulate_range_detail::super_<Range, BinaryFun>::type
{
private:
    PSTADE_OVEN_DETAIL_REQUIRES(Range, SinglePassRangeConcept);
    typedef typename accumulate_range_detail::super_<Range, BinaryFun>::type super_t;
    typedef typename super_t::iterator iter_t;
    typedef typename range_value<Range>::type value_t;

public:
    accumulate_range(Range& rng, value_t const& init, BinaryFun fun = detail::plus) :
        super_t(
            iter_t(boost::begin(rng), init, fun),
            iter_t(boost::end(rng), init, fun)
        )
    { }
};


namespace accumulate_range_detail {


    struct baby_generator
    {
        template< class Unused, class Range, class Value, class BinaryFun = detail::plus_fun >
        struct result
        {
            typedef typename egg::decay_function<BinaryFun>::type fun_t;
            typedef accumulate_range<Range, fun_t> const type;
        };

        template< class Result, class Range, class Value, class BinaryFun >
        Result call(Range& rng, Value const& init, BinaryFun& fun)
        {
            return Result(rng, init, fun);
        }

        template< class Result, class Range, class Value >
        Result call(Range& rng, Value const& init)
        {
            return Result(rng, init);
        }
    };


} // namespace accumulate_range_detail


PSTADE_EGG_FUNCTION(make_accumulate_range, accumulate_range_detail::baby_generator)
PSTADE_OVEN_RANGE_ADAPTOR(accumulated, accumulate_range_detail::baby_generator)


} } // namespace pstade::oven


PSTADE_OVEN_IS_LIGHTWEIGHT_PROXY_TEMPLATE(pstade::oven::accumulate_range, 2)


#endif
