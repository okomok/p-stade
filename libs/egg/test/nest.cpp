

// Boost.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/egg/nest.hpp>
#include "./egg_test.hpp"


#include BOOST_EGG_SUPPRESS_WARNING_BEGIN()
#include <boost/lambda/core.hpp>
#include <boost/lambda/lambda.hpp>
#include BOOST_EGG_SUPPRESS_WARNING_END()


#include <boost/egg/lazy.hpp>
#include <boost/egg/identity.hpp>
#include <boost/egg/apply.hpp>


#include "./using_egg.hpp"
namespace bll = boost::lambda;


struct T_foo
{
    typedef int result_type;

    int operator()(int i, int j, int k) const
    {
        return i - j + k;
    }
};

T_foo const foo = {};


struct T_weird
{
    typedef int result_type;

    template<class F>
    int operator()(int a, int b, F f) const
    {
        return f(b) - a;
    }
};

T_weird const weird = {};

int my_plus(int i, int j)
{
    return i + j;
}

int my_minus(int i, int j)
{
    return i - j;
}


void egg_test()
{
    using bll::_1;
    using bll::_2;

    int i6 = 6;
    int i1 = 1;
    int i3 = 3;

    {
        int i = 3, j = 9;
//        BOOST_CHECK( nest0(i) == i );
        BOOST_CHECK( nest0(_1)(i) == i );
        BOOST_CHECK( nest1(_1)(j)(i) == i );
        BOOST_CHECK( nest2(_1)(j)(j)(i) == i );
        BOOST_CHECK( nest3(_1)(j)(j)(j)(i) == i );
    }
    {
        // \x -> (\y -> (\z -> foo(x,y,z))
        typedef result_of_lazy<T_bll_bind>::type T_Bind;
        typedef result_of_lazy<T_bll_bind, T_Bind>::type T_BInd;
        typedef result_of_lazy<T_foo, T_BInd>::type T_FOO;
        T_FOO FOO;
        BOOST_CHECK( FOO(nest0(_1), nest1(_1), nest2(_1))(i6)(i1)(i3) == foo(6,1,3) );
        BOOST_CHECK( nest3(foo)(nest0(_1), nest1(_1), nest2(_1))(i6)(i1)(i3) == foo(6,1,3) );
    }
    {
        BOOST_CHECK( nest1(foo)(1,2,_1)(i3) == foo(1,2,3) );
    }
    {
        // \x -> (\y -> (\z -> foo(x,y,z))
        BOOST_CHECK( nest3(foo)(nest0(_1), nest1(_1), nest2(_1))(i6)(i1)(i3) == foo(6,1,3) );
    }
    {
        // \x -> (\y -> foo(x, y, 30))
        BOOST_CHECK( nest2(foo)(nest0(_1), nest1(_1), 30)(i6)(i1) == foo(6,1,30) );
    }
    {
        int i8 = 8, i7 = 7;
        // \x -> \y,z -> weird(y, z, \w -> my_plus(x, w))
        BOOST_CHECK( nest2(weird)(nest1(_1), nest1(_2), nest3(my_plus)(nest0(_1), nest2(_1))) (i3)(i8,i7)
            == my_plus(3, 7) - 8 );
    }
    {
        // Surprisingly, this works. I don't know why. :-)
        int i8 = 8, i7 = 7;
        // \x -> (\y -> (\z -> y(z, x)))
        BOOST_CHECK( nest3(nest1(_1))(nest2(_1), nest0(_1)) (i8)(&my_minus)(i7) // msvc-7.1 needs `&`.
            == my_minus(7, 8) );
    }
    {
        int i7 = 7;
        // \x -> (\y -> x(y, 2))
#if 0 // nest2(nest0(_1)) <=> nest2(_1) <=> unintentionally protect(protect(_1))
        BOOST_CHECK( nest2(nest0(_1))(nest1(_1), 2) (&my_minus)(i7)
            == my_minus(7, 2) );
#endif
        // \x -> (\y -> apply(x, y, 2)) // same effect as above.
        BOOST_CHECK( nest2(apply)(nest0(_1), nest1(_1), 2) (&my_minus)(i7)
            == my_minus(7, 2) );

        // \x -> (\y -> identity(x)(y, 2)) // same effect as above.
        BOOST_CHECK( nest2(lazy(identity)(nest0(_1)))(nest1(_1), 2) (&my_minus)(i7)
            == my_minus(7, 2) );
    }
    {
        int i7 = 7;
        // \x -> (\y -> x(y, 2))
        BOOST_CHECK( details::X_nest_impl2<T_bll_bind>()(nest0(_1))(nest1(_1), 2) (&my_minus)(i7)
            == my_minus(7, 2) );
    }
#if 0 // doesn't work.
    {
        int i8 = 8, i7 = 7;
        // \x -> (\y -> y-x)
        BOOST_CHECK( nest2(nest1(_1) - nest0(_1)) (i8)(i7)
            ==  7-8 );
    }
#endif
}
