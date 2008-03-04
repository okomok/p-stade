

// Boost.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/egg/level.hpp>
#include "./egg_test.hpp"


#include BOOST_EGG_SUPPRESS_WARNING_BEGIN()
#include <boost/lambda/core.hpp>
#include <boost/lambda/lambda.hpp>
#include BOOST_EGG_SUPPRESS_WARNING_END()


#include <boost/egg/lazy.hpp>


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


void egg_test()
{
    using bll::_1;

    {
        int i = 3, j = 9;
        BOOST_CHECK( level_0(i) == i );
        BOOST_CHECK( level_0(_1)(i) == i );
        BOOST_CHECK( level_1(_1)(j)(i) == i );
        BOOST_CHECK( level_2(_1)(j)(j)(i) == i );
        BOOST_CHECK( level_3(_1)(j)(j)(j)(i) == i );
    }
    {
        // \x -> (\y -> (\z -> foo(x,y,z))
        typedef result_of_lazy<T_bll_bind>::type T_Bind;
        typedef result_of_lazy<T_bll_bind, T_Bind>::type T_BInd;
        typedef result_of_lazy<T_foo, T_BInd>::type T_FOO;
        T_FOO FOO;
        BOOST_CHECK( FOO(level_0(_1), level_1(_1), level_2(_1))(6)(1)(3) == foo(6,1,3) );
        BOOST_CHECK( lazy_2(foo)(level_0(_1), level_1(_1), level_2(_1))(6)(1)(3) == foo(6,1,3) );
    }
    {
        // \x -> (\y -> (\z -> foo(x,y,z))
        typedef result_of_lazy_2<T_foo>::type T_FOO;
        T_FOO FOO;
        BOOST_CHECK( FOO(level_0(_1), level_1(_1), level_2(_1))(6)(1)(3) == foo(6,1,3) );
    }
}
