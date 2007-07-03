#include <pstade/vodka/drink.hpp>


// PStade.Fat
//
// Copyright Shunsuke Sogame 2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/fat/is_same.hpp>
#include <pstade/minimal_test.hpp>


#include <pstade/test.hpp>


namespace fat = pstade::fat;
using namespace fat;


PSTADE_TEST_IS_RESULT_OF((bool), op_is_same(int, int&))


void pstade_minimal_test()
{
    int x = 0;
    BOOST_CHECK( fat::is_same(x, x) );
    int& y = x;
    BOOST_CHECK( fat::is_same(x, y) );

    int z = 0;
    BOOST_CHECK( !fat::is_same(x, z) );
    BOOST_CHECK( !fat::is_same(y, z) );
}
