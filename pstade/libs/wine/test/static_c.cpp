#include <pstade/vodka/drink.hpp>


// PStade.Wine
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/static_c.hpp>
#include <boost/test/minimal.hpp>


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

    typedef pstade::static_c< int, 50 > a_n;
    a_n::value_type const c = a_n();
    BOOST_CHECK( c == a_n::value );
}


int test_main(int, char*[])
{
    ::test();
    return 0;
}
