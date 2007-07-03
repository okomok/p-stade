#include <pstade/vodka/drink.hpp>


// PStade.Fat
//
// Copyright Shunsuke Sogame 2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/fat/always.hpp>
#include <pstade/minimal_test.hpp>


namespace fat = pstade::fat;
using namespace fat;


void pstade_minimal_test()
{
    {
        int i = 3;
        BOOST_CHECK( always(i)() == 3 );
        always(i)() = 4;
        BOOST_CHECK( always(i)() == 4 );
        BOOST_CHECK( always(3)() == 3 );
    }
}
