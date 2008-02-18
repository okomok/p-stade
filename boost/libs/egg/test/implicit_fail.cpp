

// Boost.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/egg/implicit.hpp>
#include "./egg_test.hpp"


#include <boost/egg/by_value.hpp>
#include <boost/egg/construct.hpp>


#include "./using_egg.hpp"


typedef implicit< X_construct<>, by_value >::type T_constructor_by_value;
BOOST_EGG_CONST((T_constructor_by_value), constructor_by_value) = BOOST_EGG_IMPLICIT();


struct A
{
    A(int) {}
};


struct B
{
    B(int&) {}
};


void egg_test()
{
    A a = constructor_by_value(3); // ok.
    (void)a;

    B b = constructor_by_value(3); // should not compile,
    (void)b;
}
