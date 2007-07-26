#ifndef PSTADE_LIBS_OVEN_TEST_DETAIL_EMPTINESS_HPP
#define PSTADE_LIBS_OVEN_TEST_DETAIL_EMPTINESS_HPP


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/oven/detail/prefix.hpp>
#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>


namespace pstade { namespace oven { namespace test {


template< class Iterator >
void iter_emptiness(Iterator first, Iterator last)
{
    BOOST_CHECK(first == last);
    Iterator first1 = first;
    Iterator last1 = last;
    BOOST_CHECK(first1 == last1);
}


template< class Range > inline
void emptiness(Range const& rng)
{
    test::iter_emptiness(boost::begin(rng), boost::end(rng));
}


} } } // namespace pstade::oven::test


#endif
