#ifndef PSTADE_OVEN_JOINT_RANGE_HPP
#define PSTADE_OVEN_JOINT_RANGE_HPP


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>
#include <pstade/callable.hpp>
#include <pstade/constant.hpp>
#include <pstade/pipable.hpp>
#include "./as_lightweight_proxy.hpp"
#include "./concepts.hpp"
#include "./iter_range.hpp"
#include "./joint_iterator.hpp"
#include "./range_iterator.hpp"


namespace pstade { namespace oven {


namespace joint_range_detail {


    template< class RangeL, class RangeR >
    struct super_ :
        iter_range<
            joint_iterator<
                typename range_iterator<RangeL>::type,
                typename range_iterator<RangeR>::type
            >
        >
    { };


} // namespace joint_range_detail


template< class RangeL, class RangeR >
struct joint_range :
    joint_range_detail::super_<RangeL, RangeR>::type,
    private as_lightweight_proxy< joint_range<RangeL, RangeR> >
{
    PSTADE_CONCEPT_ASSERT((Forward<RangeL>));
    PSTADE_CONCEPT_ASSERT((Forward<RangeR>));

    typedef RangeL pstade_oven_range_base_type;

private:
    typedef typename joint_range_detail::super_<RangeL, RangeR>::type super_t;

public:
    joint_range(RangeL& rngL, RangeR& rngR) :
        super_t(
            oven::make_joint_left_iterator(boost::begin(rngL), boost::end(rngL), boost::begin(rngR)),
            oven::make_joint_right_iterator(boost::end(rngL), boost::begin(rngR), boost::end(rngR))
        )
    { }
};


struct op_make_joint_range :
    callable<op_make_joint_range>
{
    template< class Myself, class RangeL, class RangeR >
    struct apply
    {
        typedef joint_range<RangeL, RangeR> const type;
    };

    template< class Result, class RangeL, class RangeR >
    Result call(RangeL& rngL, RangeR& rngR) const
    {
        return Result(rngL, rngR);
    }
};


PSTADE_CONSTANT(make_joint_range, op_make_joint_range)
PSTADE_PIPABLE(jointed, op_make_joint_range)


} } // namespace pstade::oven


#endif
