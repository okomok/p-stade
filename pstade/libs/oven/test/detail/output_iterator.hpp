#ifndef PSTADE_LIBS_OVEN_TEST_DETAIL_OUTPUT_ITERATOR_HPP
#define PSTADE_LIBS_OVEN_TEST_DETAIL_OUTPUT_ITERATOR_HPP


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/iterator/iterator_concepts.hpp> // boost_concepts
#include <pstade/concept.hpp>
#include "./new_iterator_tests.hpp"


namespace pstade { namespace oven { namespace test {


template< class Iterator, class T >
void output_iterator(Iterator it, T v)
{
    PSTADE_CONCEPT_ASSERT((boost_concepts::WritableIteratorConcept<Iterator, T>));
    PSTADE_CONCEPT_ASSERT((boost_concepts::IncrementableIteratorConcept<Iterator>));
    boost::writable_iterator_test(it, v, v);
}


} } } // namespace pstade::oven::test


#endif
