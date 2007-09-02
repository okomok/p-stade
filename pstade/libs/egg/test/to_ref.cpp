#include <pstade/vodka/drink.hpp>


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/egg/to_ref.hpp>
#include <pstade/minimal_test.hpp>


#include <pstade/test.hpp>


namespace egg = pstade::egg;
using namespace egg;


PSTADE_TEST_IS_RESULT_OF((int const&), op_to_ref(int))
PSTADE_TEST_IS_RESULT_OF((int&), op_to_ref(int&))
PSTADE_TEST_IS_RESULT_OF((int const&), op_to_ref(int const&))
PSTADE_TEST_IS_RESULT_OF((int const&), op_to_ref(int const))

PSTADE_TEST_IS_RESULT_OF((int const&), op_to_cref(int))
PSTADE_TEST_IS_RESULT_OF((int const&), op_to_cref(int&))
PSTADE_TEST_IS_RESULT_OF((int const&), op_to_cref(int const&))
PSTADE_TEST_IS_RESULT_OF((int const&), op_to_cref(int const))

PSTADE_TEST_IS_RESULT_OF((int&), op_to_mref(int))
PSTADE_TEST_IS_RESULT_OF((int&), op_to_mref(int&))
PSTADE_TEST_IS_RESULT_OF((int&), op_to_mref(int const&))
PSTADE_TEST_IS_RESULT_OF((int&), op_to_mref(int const))


void pstade_minimal_test()
{
    {
        int i = 3;
        BOOST_CHECK( to_ref(i) == 3 );
        BOOST_CHECK( (i|to_ref()) == 3 );
        BOOST_CHECK( to_ref(3) == 3 );
    }
    {
        int i = 3;
        BOOST_CHECK( to_cref(i) == 3 );
        BOOST_CHECK( (i|to_cref()) == 3 );
        BOOST_CHECK( to_cref(3) == 3 );
    }

    {
        int i = 3;
        BOOST_CHECK( to_mref(i) == 3 );
        BOOST_CHECK( (i|to_mref()) == 3 );
        BOOST_CHECK( to_mref(3) == 3 );
        to_mref(2) = 3;
    }
}
