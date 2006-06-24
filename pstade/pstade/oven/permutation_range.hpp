#ifndef PSTADE_OVEN_PERMUTATION_RANGE_HPP
#define PSTADE_OVEN_PERMUTATION_RANGE_HPP


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
#include <boost/range/result_iterator.hpp>
#include <pstade/egg/function.hpp>
#include "./is_lightweight_proxy.hpp"
#include "./range_adaptor.hpp"


namespace pstade { namespace oven {


namespace permutation_range_detail {


    template<
        class ElementRange,
        class IndexRange
    >
    struct super_
    {
        typedef boost::iterator_range<
            boost::permutation_iterator<
                typename boost::range_result_iterator<ElementRange>::type,
                typename boost::range_result_iterator<IndexRange>::type
            >
        > type;
    };


} // namespace permutation_range_detail


template<
    class ElementRange,
    class IndexRange
>
struct permutation_range :
    permutation_range_detail::super_<ElementRange, IndexRange>::type
{
private:
    typedef typename permutation_range_detail::super_<ElementRange, IndexRange>::type super_t;
    typedef typename super_t::iterator iter_t;

public:
    explicit permutation_range(ElementRange& erng, IndexRange& irng) :
        super_t(
            iter_t(boost::begin(erng), boost::begin(irng)),
            iter_t(boost::end(erng), boost::end(irng))
        )
    { }
};


namespace permutation_range_detail {


    struct baby_generator
    {
        template< class ElementRange, class IndexRange >
        struct result
        {
            typedef const permutation_range<ElementRange, IndexRange> type;
        };

        template< class Result, class ElementRange, class IndexRange >
        Result call(ElementRange& erng, IndexRange& irng)
        {
            return Result(erng, irng);
        }
    };


} // namespace permutation_range_detail


PSTADE_EGG_FUNCTION(make_permutation_range, permutation_range_detail::baby_generator)
PSTADE_OVEN_RANGE_ADAPTOR(permutated, permutation_range_detail::baby_generator)


} } // namespace pstade::oven


PSTADE_OVEN_IS_LIGHTWEIGHT_PROXY_TEMPLATE(pstade::oven::permutation_range, 2)


#endif
