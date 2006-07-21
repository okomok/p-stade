#ifndef PSTADE_OVEN_JOINT_RANGE_HPP
#define PSTADE_OVEN_JOINT_RANGE_HPP


// PStade.Oven
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>
#include <boost/range/iterator_range.hpp>
#include <pstade/egg/function.hpp>
#include "./detail/concept_check.hpp"
#include "./is_lightweight_proxy.hpp"
#include "./joint_iterator.hpp"
#include "./range_adaptor.hpp"
#include "./range_iterator_type.hpp"


namespace pstade { namespace oven {


namespace joint_range_detail {


    template< class Range1, class Range2 >
    struct super_
    {
        typedef boost::iterator_range<
            joint_iterator<
                typename range_iterator<Range1>::type,
                typename range_iterator<Range2>::type
            >
        > type;
    };


} // namespace joint_range_detail


template< class Range1, class Range2 >
struct joint_range :
    joint_range_detail::super_<Range1, Range2>::type
{
private:
    PSTADE_OVEN_DETAIL_REQUIRES(Range1, SinglePassRangeConcept);
    PSTADE_OVEN_DETAIL_REQUIRES(Range2, SinglePassRangeConcept);
    typedef typename joint_range_detail::super_<Range1, Range2>::type super_t;

public:
    joint_range(Range1& rng1, Range2& rng2) :
        super_t(
            oven::make_joint_first_iterator(boost::begin(rng1), boost::end(rng1), boost::begin(rng2)),
            oven::make_joint_second_iterator(boost::end(rng1), boost::begin(rng2), boost::end(rng2))
        )
    { }
};


namespace joint_range_detail {


    struct baby_generator
    {
        template< class Unused, class Range1, class Range2 >
        struct result
        {
            typedef joint_range<Range1, Range2> const type;
        };

        template< class Result, class Range1, class Range2 >
        Result call(Range1& rng1, Range2& rng2)
        {
            return Result(rng1, rng2);
        }
    };


} // namespace joint_range_detail


PSTADE_EGG_FUNCTION(make_joint_range, joint_range_detail::baby_generator)
PSTADE_OVEN_RANGE_ADAPTOR(jointed, joint_range_detail::baby_generator)


} } // namespace pstade::oven


PSTADE_OVEN_IS_LIGHTWEIGHT_PROXY_TEMPLATE(pstade::oven::joint_range, 2)


#endif
