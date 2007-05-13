#include <pstade/vodka/drink.hpp>
#include <boost/test/minimal.hpp>


// PStade.Wine
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/is_old_of.hpp>


using pstade::is_old_of;


void test()
{
    int old = 3;
    BOOST_CHECK( is_old_of(old)(old + 1 - 1) );
    BOOST_CHECK( !is_old_of(old)(old + 3) );
}


int test_main(int, char*[])
{
    ::test();
    return 0;
}
