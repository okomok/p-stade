#ifndef PSTADE_OVEN_TEST_EQUALITY_HPP
#define PSTADE_OVEN_TEST_EQUALITY_HPP


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// Copyright Pavol Droba 2002-2003. Use, modification and
// distribution is subject to the Boost Software License, Version
// 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// References:
//
// [1] Pavol Droba, equals, Proposal for new string algorithms in TR2, 2006.
//     http://www.open-std.org/jtc1/sc22/wg21/docs/papers/2006/n2059.html
// [2] Pavol Droba, equals, Boost.StringAlgorithm, 2002-2004.
//     http://www.boost.org/doc/html/string_algo.html


#include "../detail/prelude.hpp"
#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>
#include <pstade/functional.hpp> // equal_to


namespace pstade { namespace oven { namespace test {


template< class Iterator, class IteratorA, class BinaryPred >
void iter_equality(
    Iterator first, Iterator last,
    IteratorA firstA, IteratorA lastA, BinaryPred pred)
{
    for (; first != last && firstA != lastA; ++first, ++firstA) {
        BOOST_CHECK(pred(*first, *firstA) && "equality test failure -- predicate returns false.");
    }

    BOOST_CHECK(firstA == lastA && "equality test failure -- testing range is shorter than expected.");
    BOOST_CHECK(first == last   && "equality test failure -- testing range is longer than expected.");
}

template< class Iterator, class IteratorA >
void iter_equality(
    Iterator first, Iterator last,
    IteratorA firstA, IteratorA lastA)
{
    test::iter_equality(first, last, firstA, lastA, equal_to);
}


template< class Range, class RangeA, class BinaryPred > inline
void equality(Range const& rng, RangeA const& rngA, BinaryPred pred)
{
    test::iter_equality(boost::begin(rng), boost::end(rng), boost::begin(rngA), boost::end(rngA), pred);
}

template< class Range, class RangeA > inline
void equality(Range const& rng, RangeA const& rngA)
{
    test::iter_equality(boost::begin(rng), boost::end(rng), boost::begin(rngA), boost::end(rngA));
}


} } } // namespace pstade::oven::test


#endif
