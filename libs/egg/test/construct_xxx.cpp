

// Boost.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/egg/construct_braced1.hpp>
#include <boost/egg/construct_braced2.hpp>
#include <boost/egg/construct.hpp>
#include <boost/egg/construct_variadic1.hpp>
#include "./egg_test.hpp"

#include <boost/egg/generator.hpp>
#include <boost/egg/by_ref.hpp>
#include <boost/egg/by_value.hpp>


#include <string>


#include "./using_egg.hpp"


struct my0
{
    std::string s1, s2;
};


struct my1
{
    my0 m;
};


struct your
{
    your(std::string x, std::string y) : s1(x), s2(y)
    { }

    std::string s1, s2;
};



struct nullary_check_pod0 { };
struct nullary_check_pod1 { nullary_check_pod0 m; };
generator<nullary_check_pod0, boost::use_default, X_construct_braced1<mpl_1, mpl_2>, nullary_check_pod0>::type const
    make_nullary_check_pod0 = BOOST_EGG_GENERATOR();
generator<nullary_check_pod1, boost::use_default, X_construct_braced2<mpl_1, mpl_2>, nullary_check_pod1>::type const
    make_nullary_check_pod1 = BOOST_EGG_GENERATOR();
generator<nullary_check_pod0, boost::use_default, X_construct<mpl_1, mpl_2>, nullary_check_pod0>::type const
    make_nullary_check_type = BOOST_EGG_GENERATOR();


void egg_test()
{
    std::string s1, s2("hello");

    my0 z = X_construct_braced1<my0, by_value>()(s1, s2);
    BOOST_CHECK(z.s2 == "hello");

    my1 a = X_construct_braced2<my1, by_perfect>()(s1, s2);
    BOOST_CHECK(a.m.s2 == "hello");

    your c = X_construct<your, by_ref>()(s1, s2);
    BOOST_CHECK(c.s2 == "hello");


    {
        nullary_check_pod0 r0 = make_nullary_check_pod0();
        nullary_check_pod1 r1 = make_nullary_check_pod1();
        nullary_check_pod0 rt = make_nullary_check_type();
    }
}
