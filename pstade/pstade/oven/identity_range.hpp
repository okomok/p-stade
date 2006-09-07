#ifndef PSTADE_OVEN_IDENTITY_RANGE_HPP
#define PSTADE_OVEN_IDENTITY_RANGE_HPP


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/range/iterator_range.hpp>
#include <pstade/egg/by_value.hpp>
#include <pstade/egg/function.hpp>
#include <pstade/egg/pipable.hpp>
#include "./as_lightweight_proxy.hpp"
#include "./detail/concept_check.hpp"
#include "./identity_iterator.hpp"
#include "./range_iterator.hpp"


namespace pstade { namespace oven {


namespace identity_range_detail {


    template< class Range, class CategoryOrTraversal >
    struct super_
    {
        typedef boost::iterator_range<
            identity_iterator<
                typename range_iterator<Range>::type,
                CategoryOrTraversal
            >
        > type;
    };


} // namespace identity_range_detail


template<
    class Range,
    class CategoryOrTraversal = boost::use_default
>
struct identity_range :
    identity_range_detail::super_<Range, CategoryOrTraversal>::type,
    private as_lightweight_proxy< identity_range<Range, CategoryOrTraversal> >
{
    typedef Range pstade_oven_range_base_type;

private:
    PSTADE_OVEN_DETAIL_REQUIRES(Range, SinglePassRangeConcept);
    typedef typename identity_range_detail::super_<Range, CategoryOrTraversal>::type super_t;

public:
    explicit identity_range(Range& rng) :
        super_t(rng)
    { }
};


namespace identity_range_detail {


    struct baby_generator
    {
        template< class Unused, class Range, class CategoryOrTraversal = boost::use_default >
        struct result
        {
            typedef typename egg::by_value<CategoryOrTraversal>::type trv_t;
            typedef identity_range<Range, trv_t> const type;
        };

        template< class Result, class Range, class CategoryOrTraversal >
        Result call(Range& rng, CategoryOrTraversal)
        {
            return Result(rng);
        }

        template< class Result, class Range >
        Result call(Range& rng)
        {
            return Result(rng);
        }
    };


} // namespace identity_range_detail


PSTADE_EGG_FUNCTION(make_identity_range, identity_range_detail::baby_generator)
PSTADE_EGG_PIPABLE(identities, identity_range_detail::baby_generator)


} } // namespace pstade::oven


#endif
