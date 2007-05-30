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
#include <algorithm> // sort
#include <boost/concept_check.hpp> // Mutable_RandomAccessIteratorConcept
#include <boost/config.hpp>
#include <boost/detail/workaround.hpp>
#include <boost/Iterator/iterator_concepts.hpp> // boost_concepts
#include <boost/Iterator/iterator_traits.hpp>
#include <boost/Iterator/new_iterator_tests.hpp>
#include <boost/ptr_container/ptr_list.hpp>
#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>
#include <pstade/concept.hpp>
#include <pstade/unused.hpp>
#include "./comb_sort.hpp"
#include "./equality.hpp"


namespace pstade { namespace oven { namespace test {


// random access
// Preconditions: [i,i+N) is a valid range
template <class Iterator, class TrueVals>
void random_access_readable_iterator_test(Iterator i, int N, TrueVals vals)
{
  boost::bidirectional_readable_iterator_test(i, vals[0], vals[1]);
  const Iterator j = i;
  int c;

  for (c = 0; c < N-1; ++c)
  {
    BOOST_TEST(i == j + c);
    BOOST_TEST(*i == vals[c]);
#if BOOST_WORKAROUND(BOOST_MSVC, BOOST_TESTED_AT(1400))
    // msvc can't order template-constructor of value_type and convertion-operator of proxy.
    typename boost::detail::iterator_traits<Iterator>::value_type x = *(j + c);
#else
    typename boost::detail::iterator_traits<Iterator>::value_type x = j[c];
#endif
    BOOST_TEST(*i == x);
    BOOST_TEST(*i == *(j + c));
    BOOST_TEST(*i == *(c + j));
    ++i;
    BOOST_TEST(i > j);
    BOOST_TEST(i >= j);
    BOOST_TEST(j <= i);
    BOOST_TEST(j < i);
  }

  Iterator k = j + N - 1;
  for (c = 0; c < N-1; ++c)
  {
    BOOST_TEST(i == k - c);
    BOOST_TEST(*i == vals[N - 1 - c]);
#if BOOST_WORKAROUND(BOOST_MSVC, BOOST_TESTED_AT(1400))
    typename boost::detail::iterator_traits<Iterator>::value_type x = *(j + (N - 1 - c));
#else
    typename boost::detail::iterator_traits<Iterator>::value_type x = j[N - 1 - c];
#endif
    BOOST_TEST(*i == x);
    Iterator q = k - c; 
    BOOST_TEST(*i == *q);
    BOOST_TEST(i > j);
    BOOST_TEST(i >= j);
    BOOST_TEST(j <= i);
    BOOST_TEST(j < i);
    --i;
  }
}


// Readable
//

template< class Iterator, class IteratorA >
void random_access_readable_iterator(Iterator first, Iterator last, IteratorA firstA, IteratorA lastA)
{
    PSTADE_CONCEPT_ASSERT((boost_concepts::RandomAccessTraversalConcept<Iterator>));
    PSTADE_CONCEPT_ASSERT((boost_concepts::ReadableIteratorConcept<Iterator>));

    typedef typename boost::iterator_value<Iterator>::type val_t;

    std::vector<val_t> const vals(firstA, lastA);
    test::random_access_readable_iterator_test(first, (int)vals.size(), vals);

    unused(last);
}


template< class Range, class RangeA > inline
void random_access_readable(Range const& rng, RangeA const& rngA)
{
    test::random_access_readable_iterator(boost::begin(rng), boost::end(rng), boost::begin(rngA), boost::end(rngA));
}


// Swappable (contents of 'rng' is abandoned.)
//

template< class Iterator, class IteratorA >
void random_access_swappable_iterator(Iterator first, Iterator last, IteratorA firstA, IteratorA lastA)
{
    PSTADE_CONCEPT_ASSERT((boost_concepts::RandomAccessTraversalConcept<Iterator>));
    // PSTADE_CONCEPT_ASSERT((boost_concepts::SwappableIteratorConcept<Iterator>)); // See "../do_iter_swap".

    typedef typename boost::iterator_value<Iterator>::type val_t;
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


// Mutable (old concept)
//

template< class Iterator, class IteratorA >
void random_access_mutable_iterator(Iterator first, Iterator last, IteratorA firstA, IteratorA lastA)
{
    PSTADE_CONCEPT_ASSERT((boost::Mutable_RandomAccessIteratorConcept<Iterator>));

    test::random_access_readable_iterator(first, last, firstA, lastA);

    typedef typename boost::iterator_value<Iterator>::type val_t;
    std::vector<val_t> vecA(firstA, lastA);
    std::sort(vecA.begin(), vecA.end());

    std::sort(first, last);

    test::iter_equality(first, last, vecA.begin(), vecA.end());
}


template< class Range, class RangeA > inline
void random_access_mutable(Range& rng, RangeA const& rngA)
{
    test::random_access_mutable_iterator(boost::begin(rng), boost::end(rng), boost::begin(rngA), boost::end(rngA));
}


} } } // namespace pstade::oven::test


#endif
