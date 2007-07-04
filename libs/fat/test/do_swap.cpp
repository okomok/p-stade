#include <pstade/vodka/drink.hpp>


// PStade.Fat
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/fat/do_swap.hpp>
#include <pstade/minimal_test.hpp>


using pstade::fat::do_swap;


void pstade_minimal_test()
{
    int x = 0;
    int y = 1;
    do_swap(x, y);
    BOOST_CHECK( x == 1 );
    BOOST_CHECK( y == 0 );
}
