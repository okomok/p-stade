#ifndef PSTADE_OVEN_STRIDE_RANGE_HPP
#define PSTADE_OVEN_STRIDE_RANGE_HPP


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/assert.hpp>
#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>
#include <boost/range/iterator_range.hpp>
#include <pstade/egg/function.hpp>
#include <pstade/egg/pipable.hpp>
#include "./as_lightweight_proxy.hpp"
#include "./detail/concept_check.hpp"
#include "./detail/debug_distance.hpp"
#include "./range_iterator.hpp"
#include "./stride_iterator.hpp"


namespace pstade { namespace oven {


namespace stride_range_detail {


    template< class ForwardRange >
    struct super_
    {
        typedef boost::iterator_range<
            stride_iterator<
                typename range_iterator<ForwardRange>::type
            >
        > type;
    };


    template< class ForwardRange, class Difference > inline
    bool is_valid_base(ForwardRange& rng, Difference length)
    {
        Difference dist = detail::debug_distance(rng);
        return dist == 0 || dist % length == 0;
    }


} // namespace stride_range_detail


template< class ForwardRange >
struct stride_range :
    stride_range_detail::super_<ForwardRange>::type,
    private as_lightweight_proxy< stride_range<ForwardRange> >
{
    typedef ForwardRange pstade_oven_range_base_type;

private:
    PSTADE_OVEN_DETAIL_REQUIRES(ForwardRange, ForwardRangeConcept);
    typedef typename stride_range_detail::super_<ForwardRange>::type super_t;
    typedef typename super_t::iterator iter_t;
    typedef typename super_t::difference_type diff_t;

public:
    stride_range(ForwardRange& rng, diff_t length, diff_t offset = 0) :
        super_t(
            iter_t(boost::begin(rng), length, offset),
            iter_t(boost::end(rng),   length, offset)
        )
    {
        BOOST_ASSERT(stride_range_detail::is_valid_base(rng, length));
    }

    diff_t length() const
    {
        return boost::begin(*this).length();
    }

    diff_t offset() const
    {
        return boost::begin(*this).offset();
    }
};


namespace stride_range_detail {


    struct baby_make
    {
        template< class Unused, class ForwardRange, class Difference, class = void >
        struct apply
        {
            typedef stride_range<ForwardRange> const type;
        };

        template< class Result, class ForwardRange, class Difference >
        Result call(ForwardRange& rng, Difference length, Difference offset)
        {
            return Result(rng, length, offset);
        }

        template< class Result, class ForwardRange, class Difference >
        Result call(ForwardRange& rng, Difference length)
        {
            return Result(rng, length);
        }
    };


} // namespace stride_range_detail


PSTADE_EGG_FUNCTION(make_stride_range, stride_range_detail::baby_make)
PSTADE_EGG_PIPABLE(stridden, stride_range_detail::baby_make)


} } // namespace pstade::oven


#endif
