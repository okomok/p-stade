

// Boost.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/egg/delete_array.hpp>
#include <pstade/unit_test.hpp>


#include <pstade/test.hpp>


#include "./using_egg.hpp"


struct udt
{};


PSTADE_TEST_IS_RESULT_OF((void), T_delete_array(int *))


PSTADE_TEST_IS_RESULT_OF((void), T_delete_array(udt *))
PSTADE_TEST_IS_RESULT_OF((void), T_delete_array(udt *))


void pstade_unit_test()
{
    {
        delete_array(new int[3]);
    }
}
