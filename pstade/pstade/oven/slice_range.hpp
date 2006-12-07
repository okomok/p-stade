#ifndef PSTADE_OVEN_SLICE_RANGE_HPP
#define PSTADE_OVEN_SLICE_RANGE_HPP


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/assert.hpp>
#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>
#include <pstade/egg/function.hpp>
#include <pstade/pipable.hpp>
#include "./as_lightweight_proxy.hpp"
#include "./concepts.hpp"
#include "./distance.hpp"
#include "./iter_range.hpp"
#include "./range_iterator.hpp"
#include "./slice_iterator.hpp"


namespace pstade { namespace oven {


namespace slice_range_detail {


    template< class Range >
    struct super_ :
        iter_range<
            slice_iterator<
                typename range_iterator<Range>::type
            >
        >
    { };


    template< class Range, class Difference > inline
    bool is_valid_base(Range& rng, Difference stride)
    {
        Difference d = oven::distance(rng);
        return d == 0 || d % stride == 0;
    }


} // namespace slice_range_detail


template< class Range >
struct slice_range :
    slice_range_detail::super_<Range>::type,
    private as_lightweight_proxy< slice_range<Range> >
{
    PSTADE_CONCEPT_ASSERT((RandomAccess<Range>));

private:
    typedef typename slice_range_detail::super_<Range>::type super_t;
    typedef typename super_t::iterator iter_t;
    typedef typename super_t::difference_type diff_t;

public:
    slice_range(Range& rng, diff_t start, diff_t stride) :
        super_t(
            iter_t(boost::begin(rng), start, stride),
            iter_t(boost::end(rng),   start, stride)
        )
    {
        BOOST_ASSERT(slice_range_detail::is_valid_base(rng, stride));
    }

    diff_t start() const
    {
        return this->begin().start();
    }

    diff_t stride() const
    {
        return this->begin().stride();
    }

    typedef Range pstade_oven_range_base_type;
};


namespace slice_range_detail {


    struct baby_make
    {
        template< class Myself, class Range, class Difference, class Difference_ >
        struct apply
        {
            typedef slice_range<Range> const type;
        };

        template< class Result, class Range, class Difference >
        Result call(Range& rng, Difference start, Difference stride) const
        {
            return Result(rng, start, stride);
        }
    };


} // namespace slice_range_detail


PSTADE_EGG_FUNCTION(make_slice_range, slice_range_detail::baby_make)
PSTADE_PIPABLE(sliced, op_make_slice_range)


} } // namespace pstade::oven


#endif
