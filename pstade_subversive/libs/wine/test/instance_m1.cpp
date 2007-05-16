#include <pstade/vodka/drink.hpp>
#include <boost/test/minimal.hpp>


// PStade.Wine
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include "./instance_m.hpp"


bool instance_m2_test();


int test_main(int, char*[])
{
    BOOST_CHECK(g_int == 12);
    BOOST_CHECK(g_char == 'a');
    g_int = 24;
    BOOST_CHECK(g_vector.empty());
    ::g_vector.push_back(g_int);

    BOOST_CHECK(::instance_m2_test());

    BOOST_CHECK(g_vector.size() == 2);
    return 0;
}
