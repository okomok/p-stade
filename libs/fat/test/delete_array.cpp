#include <pstade/vodka/drink.hpp>


// PStade.Fat
//
// Copyright Shunsuke Sogame 2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/fat/delete_array.hpp>
#include <pstade/unit_test.hpp>


#include <pstade/test.hpp>


namespace fat = pstade::fat;
using namespace fat;


struct udt
{};


PSTADE_TEST_IS_RESULT_OF((void), op_delete_array(int *))


PSTADE_TEST_IS_RESULT_OF((void), op_delete_array(udt *))
PSTADE_TEST_IS_RESULT_OF((void), op_delete_array(udt *))


void pstade_unit_test()
{
    {
        delete_array(new int[3]);
    }
}
