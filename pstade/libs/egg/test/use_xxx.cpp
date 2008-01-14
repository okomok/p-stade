#include <pstade/vodka/drink.hpp>


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/egg/use_brace1.hpp>
#include <pstade/egg/use_brace2.hpp>
#include <pstade/egg/use_constructor.hpp>
#include <pstade/minimal_test.hpp>

#include <pstade/egg/generator.hpp>


#include <string>


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
pstade::egg::generator<nullary_check_pod0, nullary_check_pod0, pstade::egg::use_brace1>::type const
    make_nullary_check_pod0 = PSTADE_EGG_GENERATOR();
pstade::egg::generator<nullary_check_pod1, nullary_check_pod1, pstade::egg::use_brace2>::type const
    make_nullary_check_pod1 = PSTADE_EGG_GENERATOR();
pstade::egg::generator<nullary_check_pod0, nullary_check_pod0, pstade::egg::use_constructor>::type const
    make_nullary_check_type = PSTADE_EGG_GENERATOR();


void pstade_minimal_test()
{
    std::string s1, s2("hello");

    my0 z = pstade::egg::use_brace1()(boost::type<my0>(), s1, s2);
    BOOST_CHECK(z.s2 == "hello");

    my1 a = pstade::egg::use_brace2()(boost::type<my1>(), s1, s2);
    BOOST_CHECK(a.m.s2 == "hello");

    your c = pstade::egg::use_constructor()(boost::type<your>(), s1, s2);
    BOOST_CHECK(c.s2 == "hello");


    {
        nullary_check_pod0 r0 = make_nullary_check_pod0();
        nullary_check_pod1 r1 = make_nullary_check_pod1();
        nullary_check_pod0 rt = make_nullary_check_type();
    }
}
