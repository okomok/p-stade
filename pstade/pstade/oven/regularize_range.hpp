#ifndef PSTADE_OVEN_REGULARIZE_RANGE_HPP
#define PSTADE_OVEN_REGULARIZE_RANGE_HPP


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/range/iterator_range.hpp>
#include <pstade/egg/function.hpp>
#include <pstade/egg/pipable.hpp>
#include "./as_lightweight_proxy.hpp"
#include "./concepts.hpp"
#include "./range_iterator.hpp"
#include "./regularize_iterator.hpp"


namespace pstade { namespace oven {


namespace regularize_range_detail {


    template< class Range >
    struct super_
    {
        typedef boost::iterator_range<
            regularize_iterator<
                typename range_iterator<Range>::type
            >
        > type;
    };


} // namespace regularize_range_detail


template< class Range >
struct regularize_range :
    regularize_range_detail::super_<Range>::type,
    private as_lightweight_proxy< regularize_range<Range> >
{
    // iterator can be neither Assignable nor DefaultConstructible.
    // PSTADE_CONCEPT_ASSERT((SinglePass<Range>));

private:
    typedef typename regularize_range_detail::super_<Range>::type super_t;

public:
    explicit regularize_range(Range& rng) :
        super_t(rng)
    { }

    typedef Range pstade_oven_range_base_type;
};


namespace regularize_range_detail {


    struct baby_make
    {
        template< class Myself, class Range  >
        struct apply
        {
            typedef regularize_range<Range> const type;
        };

        template< class Result, class Range >
        Result call(Range& rng)
        {
            return Result(rng);
        }
    };


} // namespace regularize_range_detail


PSTADE_EGG_FUNCTION(make_regularize_range, regularize_range_detail::baby_make)
PSTADE_EGG_PIPABLE(regularized, regularize_range_detail::baby_make)


} } // namespace pstade::oven


#endif
