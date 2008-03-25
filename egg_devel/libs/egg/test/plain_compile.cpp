

// Boost.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/egg/detail/plain.hpp>
#include "./egg_test.hpp"


#include <boost/mpl/assert.hpp>
#include <boost/type_traits/is_same.hpp>


using namespace boost::egg::details;


BOOST_MPL_ASSERT(( boost::is_same< int, plain<int>::type > ));
BOOST_MPL_ASSERT(( boost::is_same< int, plain<int const>::type > ));
BOOST_MPL_ASSERT(( boost::is_same< int, plain<int volatile>::type > ));
BOOST_MPL_ASSERT(( boost::is_same< int, plain<int const volatile>::type > ));

BOOST_MPL_ASSERT(( boost::is_same< int, plain<int&>::type > ));
BOOST_MPL_ASSERT(( boost::is_same< int, plain<int const&>::type > ));
BOOST_MPL_ASSERT(( boost::is_same< int, plain<int volatile&>::type > ));
BOOST_MPL_ASSERT(( boost::is_same< int, plain<int const volatile&>::type > ));


BOOST_MPL_ASSERT(( is_plain< int > ));
BOOST_MPL_ASSERT_NOT(( is_plain< int& > ));
BOOST_MPL_ASSERT_NOT(( is_plain< int const > ));
BOOST_MPL_ASSERT_NOT(( is_plain< int volatile > ));
BOOST_MPL_ASSERT_NOT(( is_plain< int const volatile > ));


void egg_test()
{ }
