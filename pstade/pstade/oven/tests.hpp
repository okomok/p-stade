#ifndef PSTADE_OVEN_TESTS_HPP
#define PSTADE_OVEN_TESTS_HPP


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/assert.hpp>
#include <boost/concept/assert.hpp>
#include <boost/foreach.hpp>
#include <boost/range/empty.hpp>
#include <boost/range/iterator_range.hpp>
#include <boost/iterator/new_iterator_tests.hpp>
#include <boost/next_prior.hpp>
#include "./algorithm.hpp"
#include "./concepts.hpp"
#include "./copy_range.hpp"
#include "./distance.hpp"
#include "./equals.hpp"
#include "./range_iterator.hpp"
#include "./range_reference.hpp"
#include "./range_value.hpp"
#include "./to_sequence.hpp"


namespace pstade { namespace oven {


template< class Range, class Vector >
void test_single_pass_readable(Range& rng, Vector const& expected)
{
    BOOST_CONCEPT_ASSERT((SinglePass<Range>));
    BOOST_CONCEPT_ASSERT((Readable<Range>));

    BOOST_ASSERT(oven::equals(rng, expected));
}


template< class Range, class Vector >
void test_single_pass_writable(Range& rng, Vector const& expected)
{
    BOOST_ASSERT(oven::distance(expected) >= 1);

    oven::test_single_pass_readable(rng, expected);
    BOOST_CONCEPT_ASSERT((Writable<Range>));

    oven::fill(rng, expected[0]);

    typedef typename range_reference<Range>::type ref_t;
    BOOST_FOREACH (ref_t r, rng) {
        BOOST_ASSERT(r == expected[0]);
    }
}


// Forward
//

template< class Range, class Vector >
void test_forward_readable(Range& rng, Vector const& expected)
{
    BOOST_ASSERT(oven::distance(expected) >= 2);
    BOOST_ASSERT(oven::distance(rng) >= 2);

    oven::test_single_pass_readable(rng, expected);

    BOOST_CONCEPT_ASSERT((Forward<Range>));
    BOOST_CONCEPT_ASSERT((Readable<Range>));

    boost::forward_readable_iterator_test(
        boost::begin(rng), boost::next(boost::begin(rng)),
        expected[0], expected[1]
    );
};


template< class Range, class Vector >
void test_forward_writable(Range& rng, Vector const& expected)
{
    BOOST_ASSERT(oven::distance(expected) >= 1);

    oven::test_forward_readable(rng, expected);
    BOOST_CONCEPT_ASSERT((Writable<Range>));

    typedef typename range_iterator<Range>::type iter_t;
    typedef typename range_iterator<Vector const>::type viter_t;
    typedef typename range_value<Vector const>::type val_t;

    Vector exp = expected;
    val_t v = exp[0];
    BOOST_ASSERT(oven::equals(
        boost::iterator_range<iter_t>( boost::begin(rng), oven::remove(rng, v)),
        boost::iterator_range<viter_t>(boost::begin(exp), oven::remove(exp, v))
    ));
}


// Bidirectional
//

template< class Range, class Vector >
void test_bidirectional_readable(Range& rng, Vector const& expected)
{
    BOOST_ASSERT(oven::distance(expected) >= 2);
    BOOST_ASSERT(oven::distance(rng) == oven::distance(expected));

    oven::test_forward_readable(rng, expected);

    BOOST_CONCEPT_ASSERT((Bidirectional<Range>));
    BOOST_CONCEPT_ASSERT((Readable<Range>));

    boost::bidirectional_readable_iterator_test(
        boost::begin(rng),
        expected[0], expected[1]
    );
}


template< class Range, class Vector >
void test_bidirectional_writable(Range& rng, Vector const& expected)
{
    oven::test_bidirectional_readable(rng, expected);
    BOOST_CONCEPT_ASSERT((Writable<Range>));

    oven::copy_backward(expected, boost::end(rng));

    BOOST_ASSERT(oven::equals(rng, expected));
}


// RandomAccess
//

template< class Range, class Vector >
void test_random_access_readable(Range& rng, Vector const& expected)
{
    BOOST_ASSERT(oven::distance(expected) >= 2);
    BOOST_ASSERT(oven::distance(rng) == oven::distance(expected));

    BOOST_CONCEPT_ASSERT((RandomAccess<Range>));
    BOOST_CONCEPT_ASSERT((Readable<Range>));

    boost::random_access_readable_iterator_test(
        boost::begin(rng), static_cast<int>(oven::distance(expected)), expected
    );
}


template< class Range, class Vector >
void test_random_access_writable(Range& rng, Vector const& expected)
{
    oven::test_random_access_readable(rng, expected);
    BOOST_CONCEPT_ASSERT((Writable<Range>));

    Vector exp = expected;

    oven::sort(exp);
    oven::sort(rng);
    BOOST_ASSERT(oven::equals(rng, exp));

    oven::random_shuffle(exp);
    oven::random_shuffle(rng);
    oven::stable_sort(exp);
    oven::stable_sort(rng);
    BOOST_ASSERT(oven::equals(rng, exp));
}


// Misc
//

template< class Range >
void test_empty(Range& rng)
{
    BOOST_ASSERT(boost::empty(rng));
}


template< class To, class From >
void test_copyable(From const& from)
{
    To to = from|copied;

    BOOST_ASSERT(oven::equals(from, oven::copy_range<To>(from)));
    BOOST_ASSERT(oven::equals(from, to));
}


} } // namespace pstade::oven


#endif
