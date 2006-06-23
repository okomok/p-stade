#include <pstade/vodka/drink.hpp>
#include <boost/test/minimal.hpp>


// PStade.Wine
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/static_c.hpp>


struct two :
    pstade::static_c<int, 2>
{ };


void foo(const int& x)
{
    BOOST_CHECK( x == 2 );
}


void bar(const int* px)
{
    BOOST_CHECK( *px == 2 );
}


void test()
{
    ::foo(::two::value);
    ::bar(&::two::value);
}


int test_main(int, char*[])
{
    ::test();
    return 0;
}
