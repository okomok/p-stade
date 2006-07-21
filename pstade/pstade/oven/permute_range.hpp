#ifndef PSTADE_OVEN_PERMUTE_RANGE_HPP
#define PSTADE_OVEN_PERMUTE_RANGE_HPP


// PStade.Oven
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/iterator/permutation_iterator.hpp>
#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>
#include <boost/range/iterator_range.hpp>
#include <pstade/egg/function.hpp>
#include "./detail/concept_check.hpp"
#include "./is_lightweight_proxy.hpp"
#include "./range_adaptor.hpp"
#include "./range_iterator_type.hpp"


namespace pstade { namespace oven {


namespace permute_range_detail {


    template<
        class ElementRange,
        class IndexRange
    >
    struct super_
    {
        typedef boost::iterator_range<
            boost::permutation_iterator<
                typename range_iterator<ElementRange>::type,
                typename range_iterator<IndexRange>::type
            >
        > type;
    };


} // namespace permute_range_detail


template<
    class ElementRange,
    class IndexRange
>
struct permute_range :
    permute_range_detail::super_<ElementRange, IndexRange>::type
{
private:
    PSTADE_OVEN_DETAIL_REQUIRES(ElementRange, RandomAccessRangeConcept);
    PSTADE_OVEN_DETAIL_REQUIRES(IndexRange, SinglePassRangeConcept);
    typedef typename permute_range_detail::super_<ElementRange, IndexRange>::type super_t;
    typedef typename super_t::iterator iter_t;

public:
    permute_range(ElementRange& erng, IndexRange& irng) :
        super_t(
            iter_t(boost::begin(erng), boost::begin(irng)),
            iter_t(boost::end(erng), boost::end(irng))
        )
    { }
};


namespace permute_range_detail {


    struct baby_generator
    {
        template< class Unused, class ElementRange, class IndexRange >
        struct result
        {
            typedef permute_range<ElementRange, IndexRange> const type;
        };

        template< class Result, class ElementRange, class IndexRange >
        Result call(ElementRange& erng, IndexRange& irng)
        {
            return Result(erng, irng);
        }
    };


} // namespace permute_range_detail


PSTADE_EGG_FUNCTION(make_permute_range, permute_range_detail::baby_generator)
PSTADE_OVEN_RANGE_ADAPTOR(permuted, permute_range_detail::baby_generator)


} } // namespace pstade::oven


PSTADE_OVEN_IS_LIGHTWEIGHT_PROXY_TEMPLATE(pstade::oven::permute_range, 2)


#endif
