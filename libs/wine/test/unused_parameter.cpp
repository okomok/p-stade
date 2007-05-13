#include <pstade/vodka/drink.hpp>
#include <boost/test/minimal.hpp>


// PStade.Wine
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/unused_parameter.hpp>


using namespace pstade;


void foo(unused_parameter = 0, unused_parameter = 0)
{
}


void test()
{
    ::foo();
    ::foo(1);
    ::foo('a', 1.0);
}


int test_main(int, char*[])
{
    ::test();
    return 0;
}
