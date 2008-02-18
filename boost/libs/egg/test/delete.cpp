

// Boost.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/egg/delete.hpp>
#include "./egg_unit_test.hpp"


#include <pstade/test.hpp>


#include "./using_egg.hpp"


struct udt
{};


PSTADE_TEST_IS_RESULT_OF((void), T_delete_(int *))


PSTADE_TEST_IS_RESULT_OF((void), T_delete_(udt *))
PSTADE_TEST_IS_RESULT_OF((void), T_delete_(udt *))


void egg_unit_test()
{
    {
        delete_(new int(3));
    }
}
