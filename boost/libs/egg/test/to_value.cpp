#include <boost/egg/pstade/vodka/drink.hpp>


// Boost.Egg
//
// Copyright Shunsuke Sogame 2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/egg/to_value.hpp>
#include <boost/egg/pstade/minimal_test.hpp>


#include <boost/egg/pstade/test.hpp>


namespace egg = pstade::egg;
using namespace egg;


PSTADE_TEST_IS_RESULT_OF((int), T_to_value(int))
PSTADE_TEST_IS_RESULT_OF((int), T_to_value(int&))
PSTADE_TEST_IS_RESULT_OF((int), T_to_value(int const&))
PSTADE_TEST_IS_RESULT_OF((int), T_to_value(int const))


void pstade_minimal_test()
{
    {
        int i = 3;
        BOOST_CHECK( to_value(i) == 3 );
        BOOST_CHECK( (i|to_value) == 3 );
        BOOST_CHECK( (i|to_value()) == 3 );
        BOOST_CHECK( to_value(3) == 3 );
    }
}
