

// Boost.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/egg/return.hpp>
#include "./egg_test.hpp"


#include BOOST_EGG_SUPPRESS_WARNING_BEGIN()
#include <boost/mpl/always.hpp>
#include <boost/lambda/core.hpp>
#include <boost/lambda/bind.hpp>
#include <boost/lambda/lambda.hpp>

#include <boost/egg/bll/result_of.hpp>
#include <boost/egg/const.hpp>
#include BOOST_EGG_SUPPRESS_WARNING_END()


struct my_fun_t
{
    template< class T >
    T operator()(T x, T y) const
    {
        return x + y;
    }
};


struct my_fun0_t
{
    int operator()() const
    {
        return 10;
    }
};


template< class FunctorWithResult >
int foo(FunctorWithResult fun)
{
    typename boost::egg::result_of_<FunctorWithResult(int)>::type x = fun(1, 2);
    return x;
}


int my_fun1(int x)
{
    return x;
}

BOOST_EGG_CONST(
    (boost::egg::result_of_return<my_fun_t, int >::type),
    fun_return_int
) = BOOST_EGG_RETURN_L {} BOOST_EGG_RETURN_R;


void egg_test()
{
    namespace egg = boost::egg;
    namespace lambda = boost::lambda;

    ::my_fun_t my_fun;

    {
        BOOST_CHECK( 3 ==
            ::foo( egg::X_return< int >()(my_fun) )
        );
    }
    {
        BOOST_CHECK( 3 ==
            egg::X_return< boost::use_default >()(&my_fun1)(3)
        );
    }

#if 0
    {
        BOOST_CHECK( 3 ==
            3  ::foo( my_fun|forwarded(boost::type<int>()) )
        );
    }
#endif
    { // make lambda perfect!
        BOOST_CHECK( 3 ==
            egg::X_return<>()(
                lambda::bind( egg::X_return< int >()(my_fun), lambda::_1, lambda::_2 )
            )(1, 2)
        );
    }

    ::my_fun0_t my_fun0;
    {
        boost::egg::result_of_<
            boost::egg::result_of_<egg::X_return< int >(my_fun0_t)>::type()
        >::type result = egg::X_return< int >()(my_fun0)();
        BOOST_CHECK( result == 10 );
    }

    {
        BOOST_CHECK( 3 ==
            egg::return_< int >(&my_fun1)(3)
        );
    }
    {
        BOOST_CHECK( 3 ==
            egg::X_return<>()(&my_fun1)(3)
        );
    }

    {
        // (lambda::_1 + lambda::_2)(1, 2); // error
        BOOST_CHECK( 3 == 
            egg::return_< int >(lambda::_1 + lambda::_2)(1, 2)
        );
        BOOST_CHECK( 3 == 
            egg::X_return<>()(lambda::_1 + lambda::_2)(1, 2)
        );
    }

    {
        egg::result_of_return< my_fun_t, int >::type perf = BOOST_EGG_RETURN({});
        BOOST_CHECK( perf(1,3) == 4);
    }
}
