#ifndef PSTADE_OVEN_INDIRECT_RANGE_HPP
#define PSTADE_OVEN_INDIRECT_RANGE_HPP


// PStade.Oven
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// See: Boost.RangeEx
//
// Copyright 2004 Eric Niebler.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/iterator/indirect_iterator.hpp>
#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>
#include <boost/range/iterator_range.hpp>
#include <pstade/egg/function.hpp>
#include "./detail/concept_check.hpp"
#include "./is_lightweight_proxy.hpp"
#include "./range_adaptor.hpp"
#include "./range_iterator_type.hpp"


namespace pstade { namespace oven {


namespace indirect_range_detail {


    template<
        class Range,
        class Value,
        class CategoryOrTraversal,
        class Reference,
        class Difference
    >
    struct super_
    {
        typedef boost::iterator_range<
            boost::indirect_iterator<
                typename range_iterator<Range>::type,
                Value,
                CategoryOrTraversal,
                Reference,
                Difference
            >
        > type;
    };


} // namespace indirect_range_detail


template<
    class Range,
    class Value = boost::use_default,
    class CategoryOrTraversal = boost::use_default,
    class Reference = boost::use_default,
    class Difference = boost::use_default
>
struct indirect_range :
    indirect_range_detail::super_<
        Range, Value, CategoryOrTraversal, Reference, Difference
    >::type
{
private:
    PSTADE_OVEN_DETAIL_REQUIRES(Range, SinglePassRangeConcept);
    typedef typename indirect_range_detail::super_<
        Range, Value, CategoryOrTraversal, Reference, Difference
    >::type super_t;

public:
    explicit indirect_range(Range& rng) :
        super_t(rng)
    { }
};


namespace indirect_range_detail {


    struct baby_generator
    {
        template< class Unused, class Range >
        struct result
        {
            typedef indirect_range<Range> const type;
        };

        template< class Result, class Range >
        Result call(Range& rng)
        {
            return Result(rng);
        }
    };


} // namespace indirect_range_detail


PSTADE_EGG_FUNCTION(make_indirect_range, indirect_range_detail::baby_generator)
PSTADE_OVEN_RANGE_ADAPTOR(indirected, indirect_range_detail::baby_generator)


} } // namespace pstade::oven


PSTADE_OVEN_IS_LIGHTWEIGHT_PROXY_TEMPLATE(pstade::oven::indirect_range, 5)


#endif
