#include <pstade/vodka/drink.hpp>
#include <boost/test/minimal.hpp>


// PStade.Wine
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/verify.hpp>


#include <pstade/is_same.hpp>


using namespace pstade;

void is_6000(int x)
{
    if (x != 6000)
        throw 0;
}


void test()
{
    int i = 0;
    verify( (++i, true) );
    BOOST_CHECK(i == 1);
    BOOST_CHECK( (i|verified) == 1 );
    BOOST_CHECK( is_same(i, verify(i)) );
    BOOST_CHECK( is_same(i, i|verified) );
    BOOST_CHECK( true || false | verified );
    BOOST_CHECK( true && true | verified );

    try {
        int j = 0;
        j|verified(&is_6000);
    } catch (int) {
        return;
    }
    BOOST_CHECK(false);
}


int test_main(int, char*[])
{
    ::test();
    return 0;
}
