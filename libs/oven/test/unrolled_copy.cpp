#define _SECURE_SCL 0
#include "./prefix.hpp"


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/oven/unrolled_copy.hpp>
#include <pstade/minimal_test.hpp>


#include <vector>
#include <pstade/oven/copied.hpp>
#include <string>
#include <pstade/oven/equals.hpp>
#include <pstade/oven/algorithm.hpp>
#include <boost/progress.hpp>


namespace oven = pstade::oven;
using namespace oven;


void pstade_minimal_test()
{
    int const count = 1000; // 100000000;
    {
        std::vector<char> b = std::string("abcdefg")|copied;
        std::vector<char> a = std::string("0123456")|copied;
        {
            boost::progress_timer t;
            for (int i = 0; i < count; ++i) {
                oven::unrolled_copy< boost::mpl::int_<7> >(b, &a[0]);
            }
        }
        BOOST_CHECK( equals(a, std::string("abcdefg")) );
        BOOST_CHECK( equals(a, b) );
    }
    {
        std::vector<char> b = std::string("abcdefg")|copied;
        std::vector<char> a = std::string("0123456")|copied;
        {
            boost::progress_timer t;
            for (int i = 0; i < count; ++i) {
                oven::copy(b, &a[0]);
            }
        }
        BOOST_CHECK( equals(a, std::string("abcdefg")) );
        BOOST_CHECK( equals(a, b) );
    }
    {
        std::string b = "abcdefg";
        std::string a = "0123456";
        {
            boost::progress_timer t;
            for (int i = 0; i < count; ++i) {
                oven::unrolled_copy_c<7>(b, &a[0]);
            }
        }
        BOOST_CHECK( equals(a, std::string("abcdefg")) );
        BOOST_CHECK( equals(a, b) );
    }
    {
        std::string b = "abcdefg";
        std::string a = "0123456";
        {
            boost::progress_timer t;
            for (int i = 0; i < count; ++i) {
                oven::copy(b, &a[0]);
            }
        }
        BOOST_CHECK( equals(a, std::string("abcdefg")) );
        BOOST_CHECK( equals(a, b) );
    }

    {
        char b[] = "abcdefg";
        char a[] = "0123456";
        {
            boost::progress_timer t;
            for (int i = 0; i < count; ++i) {
                oven::unrolled_copy_c<7>(b, &a[0]);
            }
        }
        BOOST_CHECK( equals(a, std::string("abcdefg")) );
        BOOST_CHECK( equals(a, b) );
    }
    {
        char b[] = "abcdefg";
        char a[] = "0123456";
        {
            boost::progress_timer t;
            for (int i = 0; i < count; ++i) {
                oven::copy(b, &a[0]);
            }
        }
        BOOST_CHECK( equals(a, std::string("abcdefg")) );
        BOOST_CHECK( equals(a, b) );
    }
}
