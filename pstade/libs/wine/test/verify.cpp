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


void test()
{
    int i = 0;
    pstade::verify( (++i, true) );
    BOOST_CHECK(i == 1);
    BOOST_CHECK( (i|pstade::verify) == 1 );
    BOOST_CHECK( pstade::is_same(i, pstade::verify(i)) );
    BOOST_CHECK( pstade::is_same(i, i|pstade::verify) );
    BOOST_CHECK( true || false | pstade::verify );
    BOOST_CHECK( true && true | pstade::verify );
}


int test_main(int, char*[])
{
    ::test();
    return 0;
}
