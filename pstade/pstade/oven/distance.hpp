#ifndef PSTADE_OVEN_DISTANCE_HPP
#define PSTADE_OVEN_DISTANCE_HPP


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// Question:
//
// Requires ForwardRange?


#include <iterator> // distance
#include <boost/assert.hpp>
#include <boost/iterator/iterator_categories.hpp>
#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>
#include <pstade/adl_barrier.hpp>
#include <pstade/constant.hpp>
#include <pstade/function.hpp>
#include "./concepts.hpp"
#include "./range_difference.hpp"
#include "./range_traversal.hpp"


namespace pstade { namespace oven {


namespace distance_detail {


    // Note:
    // It is possible for an iterator to be marked as RandomAccessTraversal
    // but to model InputIterator, which may trigger a slower 'std::distance',
    // because STL doesn't know the traversal concept yet. So hook it!
    template< class Result, class Range > inline
    Result aux(Range& rng, boost::random_access_traversal_tag)
    {
        return boost::end(rng) - boost::begin(rng);
    }

    template< class Result, class Range > inline
    Result aux(Range& rng, boost::single_pass_traversal_tag)
    {
        return std::distance(boost::begin(rng), boost::end(rng));
    }


    // Topic:
    // This is 'std::distance' requirement. (24.1/6)
    template< class Difference > inline
    Difference const& assert_reachable(Difference const& d)
    {
        BOOST_ASSERT(d >= 0);
        return d;
    }


    template< class Range >
    struct baby
    {
        typedef typename
            range_difference<Range>::type
        result_type;

        result_type operator()(Range& rng) const
        {
            PSTADE_CONCEPT_ASSERT((SinglePass<Range>));
            return (assert_reachable)(
                (aux<result_type>)(rng, typename range_traversal<Range>::type())
            );
        }
    };


} // namespace distance_detail


PSTADE_ADL_BARRIER(distance) { // for Boost and Std

PSTADE_FUNCTION(distance, (distance_detail::baby<_>))

} // ADL barrier


} } // namespace pstade::oven


#endif
