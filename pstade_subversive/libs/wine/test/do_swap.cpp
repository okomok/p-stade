#include <pstade/vodka/drink.hpp>
#include <boost/test/minimal.hpp>


// PStade.Wine
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/do_swap.hpp>


using pstade::do_swap;


void test()
{
    int x = 0;
    int y = 1;
    do_swap(x, y);
    BOOST_CHECK( x == 1 );
    BOOST_CHECK( y == 0 );
}


int test_main(int, char*[])
{
    ::test();
    return 0;
}
