#include <pstade/vodka/drink.hpp>


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include "./static_initialization.hpp"


op_my_id const &get_my_id2( )
{
   return my_id;
}

int j = get_my_id1().baby().touch;


op_my_idr const &get_my_idr2( )
{
   return my_idr;
}

int jr = get_my_idr1().baby().base().baby().touch;


int main()
{
    return 0;
}
