#ifndef PSTADE_LIBS_OVEN_TEST_DETAIL_SINGLE_PASS_HPP
#define PSTADE_LIBS_OVEN_TEST_DETAIL_SINGLE_PASS_HPP


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/oven/prelude.hpp>
#include <boost/iterator/iterator_concepts.hpp> // boost_concepts
#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>
#include <pstade/concept.hpp>
#include "./equality.hpp"


namespace pstade { namespace oven { namespace test {


// Readable
//

template< class Iterator, class IteratorA >
void single_pass_readable_iterator(Iterator first, Iterator last, IteratorA firstA, IteratorA lastA)
{
    PSTADE_CONCEPT_ASSERT((boost_concepts::SinglePassIteratorConcept<Iterator>));
    PSTADE_CONCEPT_ASSERT((boost_concepts::ReadableIteratorConcept<Iterator>));

    {
        BOOST_CHECK(first == first);
        BOOST_CHECK(last == last);
        BOOST_CHECK(!(first == last) ? (first != last) : true);
        BOOST_CHECK(!(first != last) ? (first == last) : true);
    }
    {
        test::iter_equality(first, last, firstA, lastA);
    }
}


template< class Range, class RangeA > inline
void single_pass_readable(Range& rng, RangeA const& rngA)
{
    test::single_pass_readable_iterator(boost::begin(rng), boost::end(rng), boost::begin(rngA), boost::end(rngA));
}


} } } // namespace pstade::oven::test


#endif
