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
#include "./concepts.hpp"
#include "./distance.hpp"
#include "./range_iterator.hpp"
#include "./stride_iterator.hpp"


namespace pstade { namespace oven {


namespace stride_range_detail {


    template< class Range >
    struct super_
    {
        typedef boost::iterator_range<
            stride_iterator<
                typename range_iterator<Range>::type
            >
        > type;
    };


    template< class Range, class Difference > inline
    bool is_valid_base(Range& rng, Difference length)
    {
        Difference d = oven::distance(rng);
        return d == 0 || d % length == 0;
    }


} // namespace stride_range_detail


template< class Range >
struct stride_range :
    stride_range_detail::super_<Range>::type,
    private as_lightweight_proxy< stride_range<Range> >
{
    PSTADE_CONCEPT_ASSERT((Forward<Range>));

private:
    typedef typename stride_range_detail::super_<Range>::type super_t;
    typedef typename super_t::iterator iter_t;
    typedef typename super_t::difference_type diff_t;

public:
    stride_range(Range& rng, diff_t length, diff_t offset = 0) :
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

    typedef Range pstade_oven_range_base_type;
};


namespace stride_range_detail {


    struct baby_make
    {
        template< class Myself, class Range, class Difference, class = void >
        struct apply
        {
            typedef stride_range<Range> const type;
        };

        template< class Result, class Range, class Difference >
        Result call(Range& rng, Difference length, Difference offset)
        {
            return Result(rng, length, offset);
        }

        template< class Result, class Range, class Difference >
        Result call(Range& rng, Difference length)
        {
            return Result(rng, length);
        }
    };


} // namespace stride_range_detail


PSTADE_EGG_FUNCTION(make_stride_range, stride_range_detail::baby_make)
PSTADE_EGG_PIPABLE(stridden, stride_range_detail::baby_make)


} } // namespace pstade::oven


#endif
