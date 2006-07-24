#include <pstade/vodka/drink.hpp>
#include <boost/test/minimal.hpp>


// PStade.Wine
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include "./statement.hpp"


void test_m1();


void test_m0()
{
    BOOST_CHECK(x == 4);
}


int test_main(int, char*[])
{
    ::test_m0();
    ::test_m1();
    return 0;
}
