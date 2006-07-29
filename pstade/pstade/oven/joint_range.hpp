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
#include "./joint_iterator.hpp"
#include "./lightweight_proxy.hpp"
#include "./range_adaptor.hpp"
#include "./range_iterator.hpp"


namespace pstade { namespace oven {


namespace joint_range_detail {


    template< class RangeL, class RangeR >
    struct super_
    {
        typedef boost::iterator_range<
            joint_iterator<
                typename range_iterator<RangeL>::type,
                typename range_iterator<RangeR>::type
            >
        > type;
    };


} // namespace joint_range_detail


template< class RangeL, class RangeR >
struct joint_range :
    joint_range_detail::super_<RangeL, RangeR>::type,
    private lightweight_proxy< joint_range<RangeL, RangeR> >
{
private:
    PSTADE_OVEN_DETAIL_REQUIRES(RangeL, SinglePassRangeConcept);
    PSTADE_OVEN_DETAIL_REQUIRES(RangeR, SinglePassRangeConcept);
    typedef typename joint_range_detail::super_<RangeL, RangeR>::type super_t;

public:
    joint_range(RangeL& rngL, RangeR& rngR) :
        super_t(
            oven::make_joint_left_iterator(boost::begin(rngL), boost::end(rngL), boost::begin(rngR)),
            oven::make_joint_right_iterator(boost::end(rngL), boost::begin(rngR), boost::end(rngR))
        )
    { }
};


namespace joint_range_detail {


    struct baby_generator
    {
        template< class Unused, class RangeL, class RangeR >
        struct result
        {
            typedef joint_range<RangeL, RangeR> const type;
        };

        template< class Result, class RangeL, class RangeR >
        Result call(RangeL& rngL, RangeR& rngR)
        {
            return Result(rngL, rngR);
        }
    };


} // namespace joint_range_detail


PSTADE_EGG_FUNCTION(make_joint_range, joint_range_detail::baby_generator)
PSTADE_OVEN_RANGE_ADAPTOR(jointed, joint_range_detail::baby_generator)


} } // namespace pstade::oven


#endif
