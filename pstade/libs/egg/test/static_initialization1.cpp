#include <pstade/vodka/drink.hpp>


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)



//#include "./pod_constant_.hpp"
#include "./static_initialization.hpp"


op_my_id const &get_my_id1( )
{
   return my_id;
}

int i = get_my_id2().baby().touch;


op_my_idr const &get_my_idr1( )
{
   return my_idr;
}

int ir = get_my_idr2().baby().base().baby().touch;


op_my_func const &get_my_func1( )
{
   return my_func;
}


op_my_idrr const &get_my_idrr1( )
{
   return my_idrr;
}

int irr = get_my_idrr2().baby().base().baby().base().baby().touch;


int ifun = get_my_func2().
    baby().
    base().
    baby().
    m_arg.
    baby().
    m_arg.
    baby().
    m_arg.
    baby().
    touch;


