#include <pstade/vodka/drink.hpp>


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/egg/aggregate0.hpp>
#include <pstade/egg/aggregate1.hpp>
#include <pstade/egg/detail/non_aggregate.hpp>
#include <pstade/minimal_test.hpp>


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


void pstade_minimal_test()
{
    std::string s1, s2("hello");
    my0 a = pstade::egg::aggregate0()(boost::type<my0>(), s1, s2);
    BOOST_CHECK(a.s2 == "hello");
    my1 b = pstade::egg::aggregate1()(boost::type<my1>(), s1, s2);
    BOOST_CHECK(b.m.s2 == "hello");
    your c = pstade::egg::detail::non_aggregate()(boost::type<your>(), s1, s2);
    BOOST_CHECK(c.s2 == "hello");
}
