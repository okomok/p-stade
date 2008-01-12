#include <boost/egg/pstade/vodka/drink.hpp>


// Boost.Egg
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/egg/apply.hpp>
#include <boost/egg/pstade/minimal_test.hpp>


#include <boost/egg/by_cref.hpp>


using namespace pstade::egg;


struct T_my_foo
{
    typedef int result_type;

    int operator()() const
    {
        return 12;
    }

    int operator()(int &x) const
    {
        return x;
    }

    int operator()(int x, int y) const
    {
        return x + y;
    }
};

T_my_foo const my_foo = {};


void foo(int,int,int,int,int,int,int,int,int) {}


void pstade_minimal_test()
{
    {
        int i = 1;
        BOOST_CHECK( apply(my_foo) == 12 );
        BOOST_CHECK( apply(my_foo, i) == i );
        BOOST_CHECK( apply(my_foo, i, 2) == 3 );
    }
    {
        // large arity check.
        X_apply<by_cref>()(&foo, 1,2,3,4,5,6,7,8,9);
    }
}

