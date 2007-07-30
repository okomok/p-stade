#include "./prefix.hpp"

// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/oven/parallel_sort.hpp>
#include <pstade/unit_test.hpp>


#include <pstade/oven/equals.hpp>
#include <pstade/oven/algorithm.hpp> // sort
#include <pstade/egg/less.hpp>
#include <boost/progress.hpp>
#include <iostream>


bool slow_less(int x, int y)
{
    for (int i = 0; i < 10000000; ++i)
        ;

    return x < y;
}


void pstade_unit_test()
{
    namespace oven = pstade::oven;
    using namespace oven;

    {
        {
            int a[] = { 1,2,13,6,1,3,4,16,3,1,7,4,2,1,7,4,2,1,3,5,1 };
            std::cout << "non-parallel:";
            boost::progress_timer t;
            oven::sort(a, &::slow_less);
        }
        {
            int a[] = { 1,2,13,6,1,3,4,16,3,1,7,4,2,1,7,4,2,1,3,5,1 };
            std::cout << "parallel:";
            boost::progress_timer t;
            parallel_sort(5, a, &::slow_less);
        }
    }
    {
        int b1[] = { 1,2,13,6,1,3,4,16,3,1,7,4,2,1,7,4,2,1,3,5,1 };
        oven::sort(b1);
        int b2[] = { 1,2,13,6,1,3,4,16,3,1,7,4,2,1,7,4,2,1,3,5,1 };
        parallel_sort(5, b2);

        BOOST_CHECK( equals(b1, b2) );
    }
    {
        int b1[] = { 1,2,13,6,1,3,4,16,3,1,7,4,2,1,7,4,2,1,3,5,1 };
        oven::sort(b1, pstade::egg::less);
        int b2[] = { 1,2,13,6,1,3,4,16,3,1,7,4,2,1,7,4,2,1,3,5,1 };
        parallel_sort(5, b2, pstade::egg::less);

        BOOST_CHECK( equals(b1, b2) );
    }
}
