#include <pstade/vodka/drink.hpp>


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/egg/copy_assign.hpp>
#include <pstade/minimal_test.hpp>


namespace egg = pstade::egg;
using namespace egg;


void pstade_minimal_test()
{
    {
        int i = 0;
        BOOST_CHECK( copy_assign(i, 3) == 3 );
        BOOST_CHECK( (i|copy_assign(4)) == 4 );
        BOOST_CHECK( i == 4 );
    }
}
