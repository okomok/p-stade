#ifndef PSTADE_OVEN_TEST_RANDOM_ACCESS_HPP
#define PSTADE_OVEN_TEST_RANDOM_ACCESS_HPP


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// Copyright (c) David Abrahams 2001.
// Copyright (c) Jeremy Siek 2001-2003.
// Copyright (c) Thomas Witt 2002.
//
// Use, modification and distribution is subject to the
// Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include "../detail/prelude.hpp"
#include <vector>
#include <boost/config.hpp>
#include <boost/detail/workaround.hpp>
#include <boost/Iterator/iterator_concepts.hpp> // boost_concepts
#include <boost/Iterator/iterator_traits.hpp>
#include <boost/ptr_container/ptr_list.hpp>
#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>
#include <pstade/concept.hpp>
#include "./bidirectional.hpp"
#include "./comb_sort.hpp"
#include "./equality.hpp"
#include "./new_iterator_tests.hpp"


namespace pstade { namespace oven { namespace test {


// Constant
//

template< class Iterator, class IteratorA >
void random_access_constant_iterator(Iterator first, Iterator last, IteratorA firstA, IteratorA lastA)
{
    PSTADE_CONCEPT_ASSERT((boost_concepts::RandomAccessTraversalConcept<Iterator>));
    PSTADE_CONCEPT_ASSERT((boost_concepts::ReadableIteratorConcept<Iterator>));
    PSTADE_CONCEPT_ASSERT((boost_concepts::LvalueIteratorConcept<Iterator>));

    {
        typedef typename boost::iterator_value<Iterator>::type val_t;
        std::vector<val_t> const vals(firstA, lastA);
        boost::random_access_readable_iterator_test(first, (int)vals.size(), vals);
    }
    {
        test::bidirectional_constant_iterator(first, last, firstA, lastA);   
    }
}


template< class Range, class RangeA > inline
void random_access_constant(Range& rng, RangeA const& rngA)
{
    test::random_access_constant_iterator(boost::begin(rng), boost::end(rng), boost::begin(rngA), boost::end(rngA));
}


// Swappable (contents of 'rng' is abandoned.)
//

template< class Iterator, class IteratorA >
void random_access_swappable_iterator(Iterator first, Iterator last, IteratorA firstA, IteratorA lastA)
{
    PSTADE_CONCEPT_ASSERT((boost_concepts::RandomAccessTraversalConcept<Iterator>));
    // PSTADE_CONCEPT_ASSERT((boost_concepts::SwappableIteratorConcept<Iterator>)); // See "../do_iter_swap".

    typedef typename boost::iterator_value<IteratorA>::type val_t;
    boost::ptr_list<val_t> lstA(firstA, lastA);
    lstA.sort();

    test::iter_comb_sort(first, last);
    test::iter_equality(first, last, lstA.begin(), lstA.end());
}


template< class Range, class RangeA > inline
void random_access_swappable(Range& rng, RangeA const& rngA)
{
    test::random_access_swappable_iterator(boost::begin(rng), boost::end(rng), boost::begin(rngA), boost::end(rngA));
}


} } } // namespace pstade::oven::test


#endif
