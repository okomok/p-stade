#ifndef PSTADE_OVEN_TEST_BIDIRECTIONAL_HPP
#define PSTADE_OVEN_TEST_BIDIRECTIONAL_HPP


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include "../detail/prelude.hpp"
#include <algorithm> // distance
#include <vector>
#include <boost/assert.hpp>
#include <boost/Iterator/iterator_concepts.hpp> // boost_concepts
#include <boost/Iterator/iterator_traits.hpp>
#include <boost/ptr_container/ptr_list.hpp>
#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>
#include <pstade/concept.hpp>
#include "./bubble_sort.hpp"
#include "./equality.hpp"
#include "./forward.hpp"
#include "./new_iterator_tests.hpp"

#if !defined(PSTADE_OVEN_TEST_REVERSED)
    #include "../reverse_iterator.hpp"
#else
    #include <boost/iterator/reverse_iterator.hpp>
#endif


namespace pstade { namespace oven { namespace test {


// Constant
//

template< class Iterator, class IteratorA >
void bidirectional_constant_iterator(Iterator first, Iterator last, IteratorA firstA, IteratorA lastA)
{
    PSTADE_CONCEPT_ASSERT((boost_concepts::BidirectionalTraversalConcept<Iterator>));
    PSTADE_CONCEPT_ASSERT((boost_concepts::ReadableIteratorConcept<Iterator>));
    PSTADE_CONCEPT_ASSERT((boost_concepts::LvalueIteratorConcept<Iterator>));
    BOOST_ASSERT(std::distance(firstA, lastA) >= 2);

    {
        typedef typename boost::iterator_value<Iterator>::type val_t;
        std::vector<val_t> const vals(firstA, lastA);
        boost::bidirectional_readable_iterator_test(first, vals[0], vals[1]);
    }
    {
#if !defined(PSTADE_OVEN_TEST_REVERSED)
        test::forward_constant_iterator(
            make_reverse_iterator(last),  make_reverse_iterator(first),
            make_reverse_iterator(lastA), make_reverse_iterator(firstA)
        );
#else
        test::forward_constant_iterator(
            boost::make_reverse_iterator(last),  boost::make_reverse_iterator(first),
            boost::make_reverse_iterator(lastA), boost::make_reverse_iterator(firstA)
        );
#endif
    }
}


template< class Range, class RangeA > inline
void bidirectional_constant(Range& rng, RangeA const& rngA)
{
    test::bidirectional_constant_iterator(boost::begin(rng), boost::end(rng), boost::begin(rngA), boost::end(rngA));

}


// Swappable (contents of 'rng' is abandoned.)
//

template< class Iterator, class IteratorA >
void bidirectional_swappable_iterator(Iterator first, Iterator last, IteratorA firstA, IteratorA lastA)
{
    PSTADE_CONCEPT_ASSERT((boost_concepts::BidirectionalTraversalConcept<Iterator>));
    // PSTADE_CONCEPT_ASSERT((boost_concepts::SwappableIteratorConcept<Iterator>)); // See "../do_iter_swap".

    typedef typename boost::iterator_value<IteratorA>::type val_t;
    boost::ptr_list<val_t> lstA(firstA, lastA);
    lstA.sort();

    test::iter_bubble_sort(first, last);
    test::iter_equality(first, last, lstA.begin(), lstA.end());
}


template< class Range, class RangeA > inline
void bidirectional_swappable(Range& rng, RangeA const& rngA)
{
    test::bidirectional_swappable_iterator(boost::begin(rng), boost::end(rng), boost::begin(rngA), boost::end(rngA));
}


} } } // namespace pstade::oven::test


#endif
