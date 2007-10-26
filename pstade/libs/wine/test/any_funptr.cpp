#include <pstade/vodka/drink.hpp>


// PStade.Wine
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/any_funptr.hpp>
#include <pstade/minimal_test.hpp>


#include <iostream>


int my_zero()
{
    return 0;
}


int my_neg(int i)
{
    return -i;
}

int g_plus_out = 0;
void my_plus(int i, int j)
{
    g_plus_out = i + j;
}

int my_mult(int i, int j, int k)
{
    return i * j * k;
}


using pstade::any_funptr;


void pstade_minimal_test()
{
    {
        any_funptr<int()> f(&my_zero);
        BOOST_CHECK(f);
        BOOST_CHECK(f() == 0);
    }
    {
        any_funptr<int(int)> f = &my_neg;
        BOOST_CHECK(f(5) == -5);
    }
    {
        any_funptr<void(int, int)> f(&my_plus);
        f(1, 2);
        BOOST_CHECK(3 == g_plus_out);
    }
    {
        any_funptr<int(int, int, int)> f(&my_mult);
        BOOST_CHECK( f );
        BOOST_CHECK(!f.empty());
        BOOST_CHECK(f(2,3,4) == 24);
        f.reset();
        BOOST_CHECK( !f );
        BOOST_CHECK(f.empty());
    }
    {
        any_funptr<int(int)> f;
        BOOST_CHECK( !f );
        BOOST_CHECK(f.empty());
        f.reset(&my_neg);
        BOOST_CHECK(!f.empty());
        BOOST_CHECK(f(5) == -5);
    }
    {
        any_funptr<int(int)> f = boost::none;
        BOOST_CHECK( !f );
        BOOST_CHECK(f.empty());

        any_funptr<int(int)> f_(&my_neg);
        BOOST_CHECK( f_ );
        BOOST_CHECK(!f_.empty());

        f_.swap(f);
        BOOST_CHECK(!f_ );
        BOOST_CHECK(f_.empty());

        BOOST_CHECK( f );
        BOOST_CHECK(!f.empty());
        BOOST_CHECK( f(3) == -3 );
    }
}
