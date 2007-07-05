#include <pstade/vodka/drink.hpp>


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/egg/delete.hpp>
#include <pstade/unit_test.hpp>


#include <pstade/test.hpp>


namespace egg = pstade::egg;
using namespace egg;


struct udt
{};


PSTADE_TEST_IS_RESULT_OF((void), op_delete_(int *))


PSTADE_TEST_IS_RESULT_OF((void), op_delete_(udt *))
PSTADE_TEST_IS_RESULT_OF((void), op_delete_(udt *))


void pstade_unit_test()
{
    {
        delete_(new int(3));
    }
}
