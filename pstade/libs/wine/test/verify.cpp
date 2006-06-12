#include <pstade/vodka/drink.hpp>
#include <boost/test/minimal.hpp>


// PStade.Wine
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/verify.hpp>


void test()
{
    int i = 0;
    PSTADE_VERIFY( (++i, true) );
    BOOST_CHECK(i == 1);
}


int test_main(int, char*[])
{
    ::test();
    return 0;
}
