

// Boost.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/egg/bll/bind.hpp>
#include "./egg_test.hpp"


#include <boost/egg/bll/placeholders.hpp>
#include "./using_egg.hpp"


struct A
{
    int foo(int i) const { return i; }
};


int bar(int i) { return i; }


struct T_buz
{
    typedef int result_type;

    result_type operator()(int i) const
    { return i; }
};

T_buz const buz = {};


void egg_test()
{
    int i3 = 3;
    {
        BOOST_CHECK( i3 == bll_bind(&bar, bll_1)(i3) );
        BOOST_CHECK( i3 == bll_bind(buz, bll_1)(i3) );
    }
    {
        A a;
        BOOST_CHECK( i3 == bll_bind(&A::foo, a, bll_1)(i3) );
    }
}
