#ifndef PSTADE_LIBS_OVEN_TEST_DETAIL_FORWARD_HPP
#define PSTADE_LIBS_OVEN_TEST_DETAIL_FORWARD_HPP


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/oven/prelude.hpp>
#include <iterator> // distance, search
#include <vector>
#include <boost/assert.hpp>
#include <boost/iterator/iterator_concepts.hpp> // boost_concepts
#include <boost/iterator/iterator_traits.hpp>
#include <boost/next_prior.hpp> // next
#include <boost/ptr_container/ptr_list.hpp>
#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>
#include <pstade/concept.hpp>
#include "./equality.hpp"
#include "./selection_sort.hpp"
#include "./new_iterator_tests.hpp"
#include "./single_pass.hpp"


namespace pstade { namespace oven { namespace test {


// Constant
//

template< class Iterator, class IteratorA >
void forward_constant_iterator(Iterator first, Iterator last, IteratorA firstA, IteratorA lastA)
{
    PSTADE_CONCEPT_ASSERT((boost_concepts::ForwardTraversalConcept<Iterator>));
    PSTADE_CONCEPT_ASSERT((boost_concepts::ReadableIteratorConcept<Iterator>));
    PSTADE_CONCEPT_ASSERT((boost_concepts::LvalueIteratorConcept<Iterator>));
    BOOST_ASSERT(std::distance(firstA, lastA) >= 2); // For 'memoized', don't traverse a tested range.

    {
        typedef typename boost::iterator_value<Iterator>::type val_t;
        std::vector<val_t> const vals(firstA, lastA);
        boost::forward_readable_iterator_test(first, boost::next(first), vals[0], vals[1]);
    }
    {
        typename boost::iterator_difference<IteratorA>::type w = std::distance(firstA, lastA) / 3;
        test::iter_equality(
            first,  std::search(first,  last,  boost::next(firstA, w), boost::next(firstA, 2 * w)),
            firstA, std::search(firstA, lastA, boost::next(firstA, w), boost::next(firstA, 2 * w))
        );
    }
    {
        test::single_pass_readable_iterator(first, last, firstA, lastA);
    }
}


template< class Range, class RangeA > inline
void forward_constant(Range& rng, RangeA const& rngA)
{
    test::forward_constant_iterator(boost::begin(rng), boost::end(rng), boost::begin(rngA), boost::end(rngA));
}


// Swappable (contents of 'rng' is abandoned.)
//

template< class Iterator, class IteratorA >
void forward_swappable_iterator(Iterator first, Iterator last, IteratorA firstA, IteratorA lastA)
{
    PSTADE_CONCEPT_ASSERT((boost_concepts::ForwardTraversalConcept<Iterator>));
    // PSTADE_CONCEPT_ASSERT((boost_concepts::SwappableIteratorConcept<Iterator>)); // See "../do_iter_swap".

    typedef typename boost::iterator_value<IteratorA>::type val_t;
    boost::ptr_list<val_t> lstA(firstA, lastA);
    lstA.sort();

    test::iter_selection_sort(first, last);
    test::iter_equality(first, last, lstA.begin(), lstA.end());
}


template< class Range, class RangeA > inline
void forward_swappable(Range& rng, RangeA const& rngA)
{
    test::forward_swappable_iterator(boost::begin(rng), boost::end(rng), boost::begin(rngA), boost::end(rngA));
}



} } } // namespace pstade::oven::test


#endif
