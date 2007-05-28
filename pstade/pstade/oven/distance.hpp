#ifndef PSTADE_OVEN_DISTANCE_HPP
#define PSTADE_OVEN_DISTANCE_HPP


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include "./detail/prelude.hpp"
#include <iterator> // distance
#include <boost/assert.hpp>
#include <boost/iterator/iterator_categories.hpp>
#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>
#include <pstade/adl_barrier.hpp>
#include <pstade/auxiliary.hpp>
#include <pstade/callable.hpp>
#include "./concepts.hpp"
#include "./range_difference.hpp"
#include "./range_traversal.hpp"


namespace pstade { namespace oven {


namespace distance_detail {


    namespace here = distance_detail;


    // STL regards a non-lvalue RandomAccess as InputIterator, hence hook it before.
    template< class Result, class Iterator > inline
    Result aux(Iterator first, Iterator last, boost::random_access_traversal_tag)
    {
        return last - first;
    }

    template< class Result, class Iterator > inline
    Result aux(Iterator first, Iterator last, boost::single_pass_traversal_tag)
    {
        return std::distance(first, last);
    }


    // This is 'std::distance' requirement. (24.1/6)
    template< class Difference > inline
    Difference assert_reachable(Difference n)
    {
        BOOST_ASSERT(0 <= n);
        return n;
    }


    struct op :
        callable<op>
    {
        template< class Myself, class Range >
        struct apply :
            range_difference<Range>
        { };

        template< class Result, class Range >
        Result call(Range& rng) const
        {
            PSTADE_CONCEPT_ASSERT((SinglePass<Range>));

            return here::assert_reachable( here::aux<Result>(
                boost::begin(rng), boost::end(rng), typename range_traversal<Range>::type()
            ) );
        }
    };


} // namespace distance_detail


PSTADE_ADL_BARRIER(distance) { // for 'boost' and 'std'
    PSTADE_AUXILIARY(0, distance, (distance_detail::op))
}


} } // namespace pstade::oven


#endif
