#define _SECURE_SCL 0
#include "./prefix.hpp"


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or reduce at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/oven/unrolled_reduce.hpp>
#include <pstade/minimal_test.hpp>


#include <vector>
#include <pstade/oven/copied.hpp>
#include <string>
#include <pstade/oven/equals.hpp>
#include <pstade/oven/numeric.hpp>
#include <boost/progress.hpp>
#include <pstade/used.hpp>


namespace oven = pstade::oven;
using namespace oven;


struct my_str_op
{
    std::string operator()(std::string x, char y) const
    {
        x.push_back(y);
        return x;
    }
};

struct my_op
{
    int operator()(int x, int y) const
    {
        return x + y;
    }
};



void pstade_minimal_test()
{
    {
        int count = 2;
        std::vector<char>b = std::string("abcdefg")|copied;
        std::string r;
        {
            boost::progress_timer t;
            for (int i = 0; i < count; ++i) {
                r = oven::unrolled_reduce_c<7>(b, std::string(), ::my_str_op());
            }
        }
        BOOST_CHECK( equals(r, std::string("abcdefg")) );
    }


    int const count = 1000; // 100000000;
    {
        int b[] = { 1,2,3,4,5,6,7 };
        int r = 0;
        {
            boost::progress_timer t;
            for (int i = 0; i < count; ++i) {
                r = oven::unrolled_reduce_c<7>(b, 0, ::my_op());
            }
        }
        pstade::used(r);
        BOOST_CHECK( r == 1+2+3+4+5+6+7 );
    }
    {
        int b[] = { 1,2,3,4,5,6,7 };
        int r = 0;
        {
            boost::progress_timer t;
            for (int i = 0; i < count; ++i) {
                r = oven::accumulate(b, 0, ::my_op());
            }
        }
        pstade::used(r);
        BOOST_CHECK( r == 1+2+3+4+5+6+7 );
    }
    {
        int b[] = { 1,2,3,4,5,6,7 };
        int r = 0;
        {
            boost::progress_timer t;
            for (int i = 0; i < count; ++i) {
                r = oven::unrolled_reduce_c<7>(b, 0, ::my_op());
            }
        }
        pstade::used(r);
        BOOST_CHECK( r == 1+2+3+4+5+6+7 );
    }
    {
        int b[] = { 1,2,3,4,5,6,7 };
        int r = 0;
        {
            boost::progress_timer t;
            for (int i = 0; i < count; ++i) {
                r = oven::accumulate(b, 0, ::my_op());
            }
        }
        pstade::used(r);
        BOOST_CHECK( r == 1+2+3+4+5+6+7 );
    }
}
