

// Boost.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

//#include "./pod_constant_.hpp"
#include "./static_initialization.hpp"
#include <boost/egg/adapted_to.hpp>
#include "./egg_test.hpp"


T_my_id const &get_my_id2( )
{
   return my_id;
}

int j = get_my_id1()|boost::egg::to_base();


T_my_idr const &get_my_idr2( )
{
   return my_idr;
}

int jr = get_my_idr1()|boost::egg::to_base();


T_my_func const &get_my_func2( )
{
   return my_func;
}


T_my_idrr const &get_my_idrr2( )
{
   return my_idrr;
}

int jrr = get_my_idrr1()|boost::egg::to_base();


int jfun  = get_my_func1()|boost::egg::to_base();
/*
= get_my_func1().
    little().
    base().
    little().
    m_arg.
    little().
    m_arg.
    little().
    m_arg.
    little().
    touch;
*/

T_pipa const &get_pipa2( )
{
   return pipa;
}

int jpi = get_pipa1()|boost::egg::to_base();


T_auxi const &get_auxi2( )
{
   return auxi;
}

int jau = get_auxi1()|boost::egg::to_base();


T_construct_int const &get_cons_int2( )
{
   return construct_int;
}

T_construct_int::little_type cons_int_ = get_cons_int1()|boost::egg::to_base();



void egg_test()
{
    BOOST_CHECK(jfun == 999);
    BOOST_CHECK(j == 999);
}
