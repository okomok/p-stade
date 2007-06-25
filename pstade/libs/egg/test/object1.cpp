#include <pstade/vodka/drink.hpp>


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/minimal_test.hpp>


#include "./object.hpp"


void pstade_minimal_test()
{
    BOOST_CHECK(0 == fun1(3));
    BOOST_CHECK('a' == fun2(5));
}
