#ifndef PSTADE_LIBS_OVEN_TEST_DETAIL_LIGHTWEIGHT_COPYABLE_HPP
#define PSTADE_LIBS_OVEN_TEST_DETAIL_LIGHTWEIGHT_COPYABLE_HPP


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/oven/detail/prefix.hpp>
#include <boost/foreach.hpp>
#include <boost/mpl/bool.hpp>


namespace pstade { namespace oven { namespace test {


bool is_lightweight_proxy(boost::mpl::true_ *)
{
    return true;
}

bool is_lightweight_proxy(boost::mpl::false_ *)
{
    return false;
}


template< class Range > inline
void lightweight_copyable(Range const& rng)
{
    BOOST_CHECK(test::is_lightweight_proxy(BOOST_FOREACH_IS_LIGHTWEIGHT_PROXY(rng)));
}


template< class Range > inline
void non_lightweight_copyable(Range const& rng)
{
    BOOST_CHECK(!test::is_lightweight_proxy(BOOST_FOREACH_IS_LIGHTWEIGHT_PROXY(rng)));
}


} } } // namespace pstade::oven::test


#endif
