#include "./prefix.hpp"

// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/oven/parallel_reduce.hpp>
#include <pstade/unit_test.hpp>


#include <pstade/oven/numeric.hpp> // accumulate
#include <pstade/egg/multiplies.hpp>
#include <pstade/egg/plus.hpp>
#include <boost/progress.hpp>
#include <iostream>
#include <string>
#include <vector>


int slow_plus(int x, int y)
{
    for (int i = 0; i < 10000000; ++i)
        ;

    return x + y;
}


void pstade_unit_test()
{
    namespace oven = pstade::oven;
    using namespace oven;

    {
        int b[] = { 1,2,13,6,1,3,4,16,3,1,7,4,2,1,7,4,2,1,3,5,1 };

        {
            std::cout << "non-parallel:";
            boost::progress_timer t;
            accumulate(b, 0, &::slow_plus);
        }
        {
            std::cout << "parallel:";
            boost::progress_timer t;
            parallel_reduce(5, b, &::slow_plus);
        }
    }
    {
        int b[] = { 1,2,13,6,1,3,4,16,3,1,7,4,2,1,7,4,2,1,3,5,1 };
        BOOST_CHECK( accumulate(b, 0, pstade::egg::plus) == parallel_reduce(5, b, pstade::egg::plus) );
    }
    {
        int b[] = { 1,2,13,6,1,3,4,16,3,1,7,4,2,1,7,4,2,1,3,5,1 };
        BOOST_CHECK( accumulate(b, 0, pstade::egg::plus) == parallel_reduce(5, b, 0, pstade::egg::plus) );
    }
    {
        int b[] = { 1,2,1,3,5,1,1,7,4,1,2,3,6,2,2,1,2,3 };
        BOOST_CHECK( accumulate(b, 1, pstade::egg::multiplies) == parallel_reduce(5, b, pstade::egg::multiplies) );
    }
    {
        int b[] = { 1,2,1,3,5,1,1,7,4,1,2,3,6,2,2,1,2,3 };
        BOOST_CHECK( accumulate(b, 1, pstade::egg::multiplies) == parallel_reduce(5, b, 1, pstade::egg::multiplies) );
    }
    {
        int b[] = { 1,2,3,4,5 };
        BOOST_CHECK( accumulate(b, 0, pstade::egg::plus) == parallel_reduce(5, b, pstade::egg::plus) );
    }
    {
        int b[] = { 1,2,3,4,5 };
        BOOST_CHECK( accumulate(b, 0, pstade::egg::plus) == parallel_reduce(5, b, 0, pstade::egg::plus) );
    }
    {
        std::vector<int> v; v.push_back(12);
        BOOST_CHECK( 12 == parallel_reduce(1, v, pstade::egg::plus) );
        BOOST_CHECK( 12 == parallel_reduce(100, v, pstade::egg::plus) );
    }
    {
        std::vector<int> v;
        BOOST_CHECK( 12 == parallel_reduce(1, v, 12, pstade::egg::plus) );
        BOOST_CHECK( 12 == parallel_reduce(100, v, 12, pstade::egg::plus) );
    }
}
