

// Boost.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/egg/curry.hpp>
#include <boost/egg/uncurry.hpp>
#include "../test/egg_test.hpp"


using namespace boost::egg;


//[code_curried_plus
int plus(int x, int y)
{
    return x + y;
}

typedef result_of_curry2<int (*)(int, int)>::type T_curried_plus;
T_curried_plus const curried_plus = BOOST_EGG_CURRY2(&::plus);

void test()
{
    BOOST_CHECK( curry2(&::plus)(4)(9) == 13 );
    BOOST_CHECK( curried_plus(4)(9) == plus(4, 9) );
    BOOST_CHECK( uncurry(curry2(plus))(4, 9) == 13 );
}
//]


void egg_test()
{
    test();
}
