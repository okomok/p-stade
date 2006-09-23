#ifndef PSTADE_OVEN_TESTS_HPP
#define PSTADE_OVEN_TESTS_HPP


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// Pending...
//


#include <algorithm>
#include <iterator> // back_inserter
#include <vector>
#include <boost/next_prior.hpp>
#include <boost/range/begin.hpp>
#include <boost/range/empty.hpp>
#include <boost/range/end.hpp>
#include <boost/range/iterator_range.hpp>
#include <boost/range/rbegin.hpp>
#include <boost/range/rend.hpp>
#include "./detail/concept_check.hpp"
#include "./equals.hpp"
#include "./range_iterator.hpp"
#include "./range_value.hpp"


namespace pstade { namespace oven {


template< class Range >
bool test_emptiness(Range& )
{
    bool result = true;

    Range emptyRng;
    result = result && boost::empty(emptyRng);

    return result;
}


template< class Range >
bool test_single_pass(Range& rng)
{
    BOOST_ASSERT(!boost::empty(rng));

    bool result = true;

    // convertibility check
    typedef typename range_iterator_const<Range>::type citer_t;
    citer_t cit = boost::begin(rng);
    (void)cit; // unused

    // mutability check
    typedef typename range_value<Range>::type val_t;
    val_t v = *boost::begin(rng);
    *boost::begin(rng) = v;
    result = result && *boost::begin(rng) == v;

    return result;
}


template< class Range >
bool test_forward(Range& rng)
{
    detail::requires< boost::ForwardRangeConcept<Range> >();

    bool result = oven::test_single_pass(rng);

    typedef typename range_value<Range>::type val_t;

    std::vector<val_t> saved;
    std::copy(boost::begin(rng), boost::end(rng), std::back_inserter(saved));
    std::rotate(boost::begin(saved), boost::next(boost::begin(saved)), boost::end(saved));

    std::rotate(boost::begin(rng), boost::next(boost::begin(rng)), boost::end(rng));

    return result && oven::equals(saved, rng);
};


template< class Range >
bool test_bidirectional(Range& rng)
{
    detail::requires< boost::BidirectionalRangeConcept<Range> >();

    bool result = oven::test_forward(rng);

    typedef typename range_value<Range>::type val_t;

    std::vector<val_t> saved;
    std::copy(boost::begin(rng), boost::end(rng), std::back_inserter(saved));

    result = result && oven::equals(
        boost::make_iterator_range(boost::rbegin(saved), boost::rend(saved)),
        boost::make_iterator_range(boost::rbegin(rng), boost::rend(rng))
    );

    return result;
}


template< class Range >
bool test_random_access(Range& rng)
{
    detail::requires< boost::RandomAccessRangeConcept<Range> >();

    bool result = oven::test_bidirectional(rng);

    typedef typename range_value<Range>::type val_t;

    std::vector<val_t> saved;
    std::copy(boost::begin(rng), boost::end(rng), std::back_inserter(saved));
    std::sort(boost::begin(saved), boost::end(saved));

    std::random_shuffle(boost::begin(rng), boost::end(rng));
    std::sort(boost::begin(rng), boost::end(rng));
    result = result && oven::equals(rng, saved);

    std::random_shuffle(boost::begin(rng), boost::end(rng));
    std::stable_sort(boost::begin(rng), boost::end(rng));
    result = result && oven::equals(rng, saved);

    std::random_shuffle(boost::begin(rng), boost::end(rng));
    std::partial_sort(boost::begin(rng), boost::end(rng), boost::end(rng));
    result = result && oven::equals(rng, saved);

    return result;
}


} } // namespace pstade::oven


#endif
