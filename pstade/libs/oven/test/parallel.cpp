#include "./prefix.hpp"

// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/oven/parallel_equals.hpp>
#include <pstade/unit_test.hpp>


#include <pstade/oven/equals.hpp>
#include <pstade/oven/algorithm.hpp> // sort
#include <pstade/egg/less.hpp>
#include <boost/progress.hpp>
#include <iostream>
#include <string>

#include <pstade/oven/memoized.hpp>


bool slow_less(int x, int y)
{
    for (int i = 0; i < 10000000; ++i)
        ;

    return x < y;
}

bool slow_equal_to(int x, int y)
{
    for (int i = 0; i < 10000000; ++i)
        ;

    return x == y;
}


void pstade_unit_test()
{
    namespace oven = pstade::oven;
    using namespace oven;

    {
        int b1[] = { 1,2,13,6,1,3,4,16,3,1,7,4,2,1,7,4,2,1,3,5,1 };
        int b2[] = { 1,2,13,6,1,3,4,16,3,1,7,4,2,1,7,4,2,1,3,5,1 };

        BOOST_CHECK( parallel_equals(5, b1|memoized, b2, &::slow_equal_to) );
    }
}
