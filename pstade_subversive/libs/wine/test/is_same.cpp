#include <pstade/vodka/drink.hpp>
#include <boost/test/minimal.hpp>


// PStade.Wine
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/is_same.hpp>


void test()
{
    int x = 0;
    BOOST_CHECK( pstade::is_same(x, x) );
    int& y = x;
    BOOST_CHECK( pstade::is_same(x, y) );

    int z = 0;
    BOOST_CHECK( !pstade::is_same(x, z) );
    BOOST_CHECK( !pstade::is_same(y, z) );
}


int test_main(int, char*[])
{
    ::test();
    return 0;
}
