#include "./prefix.hpp"

// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/oven/parallel_equals.hpp>
#include <pstade/unit_test.hpp>


#include <boost/progress.hpp>
#include <pstade/oven/identities.hpp>
#include <iostream>
#include <string>


bool int_equal(int x, int y)
{
    for (int i = 0; i < 10000000; ++i)
        ;

    return x == y;
}

bool always_not_equal(int, int)
{
    for (int i = 0; i < 10000; ++i)
        ;

    return false;
}


void pstade_unit_test()
{
    namespace oven = pstade::oven;
    using namespace oven;

    {
        int a[] = { 1,2,13,6,1,3,4,16,3,1,7,4,2,1,7,4,2,1,3,5,1 };
        int b[] = { 1,2,13,6,1,3,4,16,3,1,7,4,2,1,7,4,2,1,3,5,1 };

        {
            std::cout << "non-parallel:";
            boost::progress_timer t;
            BOOST_CHECK( equals(a, b, &::int_equal) );
        }
        {
            std::cout << "parallel:";
            boost::progress_timer t;
            BOOST_CHECK( parallel_equals(3, a, b, &::int_equal) );
        }
    }
    {
        int a[] = { 1,2,13,6,1,3,4,16,3,1,7,4,2,1,7,4,2,1,3,5,1 };
        int b[] = { 1,2,13,6,1,3,4,16,3,1,7,4,2,1,7,4,2,1,3,5,1 };
        BOOST_CHECK( parallel_equals(3, a, b) );
        BOOST_CHECK( parallel_equals(0, a, b) ); // default grainsize
        BOOST_CHECK( parallel_equals(3, a, b|identities, &::int_equal) );
        BOOST_CHECK( !parallel_equals(3, a, b, &::always_not_equal) );
    }
    {
        int a[] = { 1,2,13,6,1,3,4,16,3,1, 7,4,2,1,7,4,2,1,3,5,1 };
        int b[] = { 1,2,13,6,1,3,4,16,3,99,7,4,2,1,7,4,2,1,3,5,1 };
        BOOST_CHECK( !parallel_equals(3, a, b) );
        BOOST_CHECK( !parallel_equals(3, a, b, &::int_equal) );
    }


    {
        int a[] = { 1,2,13,6,1,3,4,16,3,1,7,4,2,1,7,4,2,1,3,5,1 };
        int b[] = { 1,2,13,6,1,3,4,16,3,1,7,4,2,1,7,4,2,1,3 };
        BOOST_CHECK( !parallel_equals(3, a, b) );
        BOOST_CHECK( !parallel_equals(3, a, b, &::int_equal) );
    }
    {
        int a[] = { 1,2,13,6,1,3,4,16,3,1,7,4,2,1,7,4,2,1,3,5 };
        int b[] = { 1,2,13,6,1,3,4,16,3,1,7,4,2,1,7,4,2,1,3,5,1 };
        BOOST_CHECK( !parallel_equals(3, a, b) );
        BOOST_CHECK( !parallel_equals(3, a, b, &::int_equal) );
    }
    {
        int a[] = { 1,2,13,6,1,3,4,16,3,1,7,4,2,1,7,4,2,1,3,5,1 };
        int b[] = { 1,2,13,6,1,3,4,16,3,1,7,4,2,1,7,4,2,1,3 };
        BOOST_CHECK( !parallel_equals(3, a|identities(in_forward), b) );
        BOOST_CHECK( !parallel_equals(3, a|identities(in_forward), b, &::int_equal) );
    }
    {
        int a[] = { 1,2,13,6,1,3,4,16,3,1,7,4,2,1,7,4,2,1,3,5 };
        int b[] = { 1,2,13,6,1,3,4,16,3,1,7,4,2,1,7,4,2,1,3,5,1 };
        BOOST_CHECK( !parallel_equals(3, a, b|identities(in_forward)) );
        BOOST_CHECK( !parallel_equals(3, a, b|identities(in_forward), &::int_equal) );
    }


    {
        std::string b("0123401234");
        std::string a = b;
        BOOST_CHECK( parallel_equals(5, a, b) );
    }
    {
        std::string b;
        std::string a;
        BOOST_CHECK( parallel_equals(1, a, b) );
        BOOST_CHECK( parallel_equals(100, a, b) );
    }
    {
        std::string b("0123401234");
        std::string a = b;
        BOOST_CHECK( parallel_equals(5, a|identities(in_forward), b) );
    }
    {
        std::string b;
        std::string a;
        BOOST_CHECK( parallel_equals(1, a|identities(in_forward), b) );
        BOOST_CHECK( parallel_equals(100, a|identities(in_forward), b) );
    }
}
