#include <pstade/vodka/drink.hpp>


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/egg/new_shared_array.hpp>
#include <pstade/unit_test.hpp>


#include <pstade/test.hpp>


namespace egg = pstade::egg;
using namespace egg;


struct udt
{
};


PSTADE_TEST_IS_RESULT_OF((boost::shared_array<int>), X_new_shared_array<int>(int))
PSTADE_TEST_IS_RESULT_OF((boost::shared_array<int>), X_new_shared_array<int>(int))


PSTADE_TEST_IS_RESULT_OF((boost::shared_array<udt>), X_new_shared_array<udt>(int))
PSTADE_TEST_IS_RESULT_OF((boost::shared_array<udt const>), X_new_shared_array<udt const>(int))


void pstade_unit_test()
{
    {
        boost::shared_array<udt> p = X_new_shared_array<udt>()(12);
        (void)p;
    }
}
