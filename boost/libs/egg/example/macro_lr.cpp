#include <boost/egg/pstade/vodka/drink.hpp>


// Boost.Egg
//
// Copyright Shunsuke Sogame 2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/egg/pstade/minimal_test.hpp>


#include <boost/egg/curry.hpp>
#include <boost/egg/uncurry.hpp>
#include <boost/egg/compose.hpp>
#include <iostream>


using namespace pstade::egg;


struct T_my_plus
{
    typedef int result_type;

    int operator()(int x, int y) const
    {
        std::cout << m_msg << ", version: " << m_version << std::endl;
        return x + y;
    }

    char const *m_msg;
    int m_version;
};

struct T_my_negate
{
    typedef int result_type;

    int operator()(int x) const
    {
        return -x;
    }
};

result_of_curry2<
    result_of_compose<
        T_my_negate,
        T_my_plus
    >::type
>::type const my_func
    =
BOOST_EGG_CURRY2_L
    BOOST_EGG_COMPOSE_L
        {}
    BOOST_EGG_COMPOSE_M
        {"my_plus call", 198}
    BOOST_EGG_COMPOSE_R
BOOST_EGG_CURRY2_R
    ;

result_of_curry2<
    result_of_uncurry<
        result_of_curry2<T_my_plus>::type
    >::type
>::type const my_func2
    = 
BOOST_EGG_CURRY2_L
    BOOST_EGG_UNCURRY_L
        BOOST_EGG_CURRY2_L {"my_plus call", 198} BOOST_EGG_CURRY2_R
    BOOST_EGG_UNCURRY_R
BOOST_EGG_CURRY2_R
    ;


void pstade_minimal_test()
{
    BOOST_CHECK( my_func(3)(4) == -7 );
    BOOST_CHECK( my_func2(3)(4) == 7 );
}
