#include <pstade/vodka/drink.hpp>
#include <boost/test/minimal.hpp>


// PStade.Wine
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include "./constant_m.hpp"


bool test_constant_m2();


void test()
{
    BOOST_CHECK(::g_int == 0);
    BOOST_CHECK(::g_vector.empty());
    BOOST_CHECK(::test_constant_m2());
}


int test_main(int, char*[])
{
    ::test();
    return 0;
}
