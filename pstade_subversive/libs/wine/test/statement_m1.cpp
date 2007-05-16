#include <pstade/vodka/drink.hpp>
#include <boost/test/minimal.hpp>


// PStade.Wine
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include "./statement.hpp"


bool test_m2();


void test_m1()
{
    BOOST_CHECK(x == 4);
}


int test_main(int, char*[])
{
    ::test_m1();
    BOOST_CHECK(::test_m2());
    return 0;
}
