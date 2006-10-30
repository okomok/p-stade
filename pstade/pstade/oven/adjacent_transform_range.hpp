#ifndef PSTADE_OVEN_ADJACENT_TRANSFORM_RANGE_HPP
#define PSTADE_OVEN_ADJACENT_TRANSFORM_RANGE_HPP


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>
#include <pstade/egg/function.hpp>
#include <pstade/egg/pipable.hpp>
#include <pstade/pass_by.hpp>
#include "./adjacent_transform_iterator.hpp"
#include "./as_lightweight_proxy.hpp"
#include "./concepts.hpp"
#include "./iter_range.hpp"
#include "./range_iterator.hpp"


namespace pstade { namespace oven {


namespace adjacent_transform_range_detail {


    template< class Range, class BinaryFun, class Reference, class Value >
    struct super_ :
        iter_range<
            adjacent_transform_iterator<
                typename range_iterator<Range>::type,
                BinaryFun, Reference, Value
            >
        >
    { };


} // namespace adjacent_transform_range_detail


template<
    class Range,
    class BinaryFun,
    class Reference = boost::use_default,
    class Value     = boost::use_default
>
struct adjacent_transform_range :
    adjacent_transform_range_detail::super_<Range, BinaryFun, Reference, Value>::type,
    private as_lightweight_proxy< adjacent_transform_range<Range, BinaryFun, Reference, Value> >
{
    PSTADE_CONCEPT_ASSERT((Forward<Range>));
    // PSTADE_CONCEPT_ASSERT((Readable<Range>));
    typedef BinaryFun function_type;

private:
    typedef typename adjacent_transform_range_detail::super_<Range, BinaryFun, Reference, Value>::type super_t;

public:
    adjacent_transform_range(Range& rng, BinaryFun const& fun) :
        super_t(
            oven::make_adjacent_transform_begin_iterator<Reference, Value>(boost::begin(rng), boost::end(rng), fun),
            oven::make_adjacent_transform_end_iterator  <Reference, Value>(boost::begin(rng), boost::end(rng), fun)
        )
    { }

    typedef Range pstade_oven_range_base_type;
};


namespace adjacent_transform_range_detail {


    struct baby_make
    {
        template< class Myself, class Range, class BinaryFun >
        struct apply
        {
            typedef typename pass_by_value<BinaryFun>::type fun_t;
            typedef adjacent_transform_range<Range, fun_t> const type;
        };

        template< class Result, class Range, class BinaryFun >
        Result call(Range& rng, BinaryFun& fun)
        {
            return Result(rng, fun);
        }
    };


} // namespace adjacent_transform_range_detail


PSTADE_EGG_FUNCTION(make_adjacent_transform_range, adjacent_transform_range_detail::baby_make)
PSTADE_EGG_PIPABLE(adjacent_transformed, adjacent_transform_range_detail::baby_make)


} } // namespace pstade::oven


#endif
