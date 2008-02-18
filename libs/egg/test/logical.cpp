

// Boost.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/egg/functional.hpp>
#include "./egg_test.hpp"


#include "./using_egg.hpp"


void egg_test()
{
    BOOST_CHECK( logical_and(10 ,20) );
    BOOST_CHECK( !logical_and(10 ,0) );
    BOOST_CHECK( logical_or(10 ,20) );
    BOOST_CHECK( !logical_not(10) );
    BOOST_CHECK( logical_not(0) );
}
