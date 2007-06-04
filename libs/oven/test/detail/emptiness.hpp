#ifndef PSTADE_OVEN_TEST_EMPTINESS_HPP
#define PSTADE_OVEN_TEST_EMPTINESS_HPP


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/oven/detail/prelude.hpp>
#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>


namespace pstade { namespace oven { namespace test {


template< class Iterator >
void iter_emptiness(Iterator first, Iterator last)
{
    BOOST_CHECK(first == last);
    Iterator first_ = first;
    BOOST_CHECK(first_ == last);
    Iterator last_ = last;
    BOOST_CHECK(last_ == last);
    BOOST_CHECK(first_ == last_);
    first = last_;
    BOOST_CHECK(first == last_);
    last = first_;
    BOOST_CHECK(last == first_);
    BOOST_CHECK(last == first);
}


template< class Range > inline
void emptiness(Range const& rng)
{
    test::iter_emptiness(boost::begin(rng), boost::end(rng));
}


} } } // namespace pstade::oven::test


#endif
