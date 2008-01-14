#include <pstade/vodka/drink.hpp>


// PStade.Wine
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/plain.hpp>
#include <pstade/lightweight_test.hpp>


#include <boost/mpl/assert.hpp>
#include <boost/type_traits/is_same.hpp>


BOOST_MPL_ASSERT(( boost::is_same< int, pstade::plain<int>::type > ));
BOOST_MPL_ASSERT(( boost::is_same< int, pstade::plain<int const>::type > ));
BOOST_MPL_ASSERT(( boost::is_same< int, pstade::plain<int volatile>::type > ));
BOOST_MPL_ASSERT(( boost::is_same< int, pstade::plain<int const volatile>::type > ));

BOOST_MPL_ASSERT(( boost::is_same< int, pstade::plain<int&>::type > ));
BOOST_MPL_ASSERT(( boost::is_same< int, pstade::plain<int const&>::type > ));
BOOST_MPL_ASSERT(( boost::is_same< int, pstade::plain<int volatile&>::type > ));
BOOST_MPL_ASSERT(( boost::is_same< int, pstade::plain<int const volatile&>::type > ));


BOOST_MPL_ASSERT(( pstade::is_plain< int > ));
BOOST_MPL_ASSERT_NOT(( pstade::is_plain< int& > ));
BOOST_MPL_ASSERT_NOT(( pstade::is_plain< int const > ));
BOOST_MPL_ASSERT_NOT(( pstade::is_plain< int volatile > ));
BOOST_MPL_ASSERT_NOT(( pstade::is_plain< int const volatile > ));


void pstade_lightweight_test()
{}

