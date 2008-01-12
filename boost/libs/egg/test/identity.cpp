#include <boost/egg/pstade/vodka/drink.hpp>


// Boost.Egg
//
// Copyright Shunsuke Sogame 2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/egg/identity.hpp>
#include <boost/egg/pstade/minimal_test.hpp>


#include <boost/egg/pstade/test.hpp>
#include <boost/egg/by_value.hpp>


namespace egg = pstade::egg;
using namespace egg;


PSTADE_TEST_IS_RESULT_OF((const int&), T_identity(int))
PSTADE_TEST_IS_RESULT_OF((int&), T_identity(int&))
PSTADE_TEST_IS_RESULT_OF((const int&), T_identity(int const&))
PSTADE_TEST_IS_RESULT_OF((const int&), T_identity(int const))

PSTADE_TEST_IS_RESULT_OF((int), X_identity<by_value>(int&))


void pstade_minimal_test()
{
    int x = 0;
    BOOST_CHECK( &(identity(x)) == &x );
    int& y = x;
    BOOST_CHECK( &(identity(x)) == &y );

    int z = 0;
    BOOST_CHECK( &(identity(x)) != &z );
}
