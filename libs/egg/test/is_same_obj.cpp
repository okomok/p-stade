

// Boost.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/egg/is_same.hpp>
#include "./egg_test.hpp"
#include "./check_is_result_of.hpp"


#include "./using_egg.hpp"


CHECK_IS_RESULT_OF((bool), T_is_same(int, int&))


void egg_test()
{
    int x = 0;
    BOOST_CHECK( egg::is_same(x, x) );
    int& y = x;
    BOOST_CHECK( egg::is_same(x, y) );

    int z = 0;
    BOOST_CHECK( !egg::is_same(x, z) );
    BOOST_CHECK( !egg::is_same(y, z) );
}
