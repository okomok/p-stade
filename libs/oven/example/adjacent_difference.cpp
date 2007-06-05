#include <pstade/vodka/drink.hpp>
#include <boost/test/minimal.hpp>


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include "../test/detail/v1_tests.hpp"
#include <pstade/oven.hpp>


#include <iostream>
#include <pstade/functional.hpp>
#include <boost/lambda/core.hpp>
#include <boost/lambda/lambda.hpp>


namespace lambda = boost::lambda;
namespace oven = pstade::oven;
using namespace oven;


void test()
{
    int A[] = { 1,4,9,16,25,36,49,64,81,100 };

    BOOST_CHECK( equals(
        A |
            adjacent_transformed(regular(lambda::_2 - lambda::_1)) |
            scanned(1, regular(lambda::_1 + lambda::_2)),
        A
    ) );
}


int test_main(int, char*[])
{
    ::test();
    return 0;
}
