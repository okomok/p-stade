#ifndef PSTADE_OVEN_DISTANCE_HPP
#define PSTADE_OVEN_DISTANCE_HPP


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <iterator> // distance
#include <boost/iterator/iterator_categories.hpp> // traversal_tag's
#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>
#include <pstade/adl_barrier.hpp>
#include <pstade/egg/function.hpp>
#include "./detail/concept_check.hpp"
#include "./range_difference.hpp"
#include "./range_traversal.hpp"


namespace pstade { namespace oven {


namespace distance_detail {


    // Note:
    // It is possible for an iterator to be marked as RandomAccessTraversal
    // but model InputIterator, which may trigger a slower 'std::distance',
    // because STL doesn't know the traversal concept yet. So hook it!
    //

    template< class Result, class Range > inline
    Result aux(Range const& rng, boost::random_access_traversal_tag)
    {
        return boost::end(rng) - boost::begin(rng);
    }

    template< class Result, class Range > inline
    Result aux(Range const& rng, boost::single_pass_traversal_tag)
    {
        return std::distance(boost::begin(rng), boost::end(rng));
    }


    struct baby
    {
        template< class Unused, class Range >
        struct result :
            range_difference<Range>
        { };

        template< class Result, class Range >
        Result call(Range const& rng)
        {
            detail::requires< boost::SinglePassRangeConcept<Range> >();

            typedef typename range_traversal<Range>::type trv_t;
            return distance_detail::aux<Result>(rng, trv_t());
        }
    };


} // namespace distance_detail


PSTADE_ADL_BARRIER(distance) { // for Boost

PSTADE_EGG_FUNCTION(distance, distance_detail::baby)

} // ADL barrier


} } // namespace pstade::oven


#endif
