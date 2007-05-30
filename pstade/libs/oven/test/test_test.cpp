

// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/minimal_test.hpp>
#include <pstade/oven/test/bubble_sort.hpp>
#include <pstade/oven/test/comb_sort.hpp>
#include <pstade/oven/test/nc_list.hpp>
#include <pstade/oven/test/nc_slist.hpp>
#include <pstade/oven/test/nc_string.hpp>
#include <pstade/oven/test/nc_vector.hpp>
#include <pstade/oven/test/samples.hpp>
#include <pstade/oven/test/equality.hpp>
#include <pstade/oven/test/random_access.hpp>
#include <pstade/oven/test/bidirectional.hpp>
#include <pstade/oven/test/forward.hpp>


#include <pstade/oven/ptr_container.hpp>
#include <boost/ptr_container/ptr_list.hpp>
#include <boost/ptr_container/ptr_vector.hpp>
#include "./core.hpp"


namespace oven = pstade::oven;
using namespace oven;


void test_sort()
{
    {
        boost::ptr_vector<test::nc_string> vec;
        vec.push_back(new test::nc_string("c"));
        vec.push_back(new test::nc_string("a"));
        vec.push_back(new test::nc_string("d"));
        vec.push_back(new test::nc_string("b"));

        test::bubble_sort(vec);
        BOOST_CHECK( vec[0] == std::string("a") );
        BOOST_CHECK( vec[1] == std::string("b") );
        BOOST_CHECK( vec[2] == std::string("c") );
        BOOST_CHECK( vec[3] == std::string("d") );
    }
    {
        boost::ptr_vector<test::nc_string> vec;
        vec.push_back(new test::nc_string("c"));
        vec.push_back(new test::nc_string("a"));
        vec.push_back(new test::nc_string("d"));
        vec.push_back(new test::nc_string("b"));

        test::comb_sort(vec);
        BOOST_CHECK( vec[0] == std::string("a") );
        BOOST_CHECK( vec[1] == std::string("b") );
        BOOST_CHECK( vec[2] == std::string("c") );
        BOOST_CHECK( vec[3] == std::string("d") );
    }
    {
        boost::ptr_vector<test::nc_string> vec;
        vec.push_back(new test::nc_string("c"));
        vec.push_back(new test::nc_string("a"));
        vec.push_back(new test::nc_string("d"));
        vec.push_back(new test::nc_string("b"));

        test::selection_sort(vec);
        BOOST_CHECK( vec[0] == std::string("a") );
        BOOST_CHECK( vec[1] == std::string("b") );
        BOOST_CHECK( vec[2] == std::string("c") );
        BOOST_CHECK( vec[3] == std::string("d") );
    }
}


void test_equality()
{
    {
        test::nc_string rng(test::sample_string());
        test::equality(rng, test::sample_string());
    }
    {
        test::nc_vector<int> rng(test::sample_ints());
        test::equality(rng, test::sample_ints());
    }
}


void test_emptiness()
{
}


void test_random_access()
{
    {
        test::nc_string rng(test::sample_string());
        test::random_access_readable(rng, test::sample_string());
    }
    {
        test::nc_string rng(test::sample_string());
        test::random_access_swappable(rng, test::sample_string());
    }
    {
        test::nc_string rng(test::sample_string());
        test::random_access_mutable(rng, test::sample_string());
    }
    {
        test::nc_vector<int> rng(test::sample_ints());
        test::random_access_readable(rng, test::sample_ints());
    }
    {
        boost::ptr_vector<test::nc_int> rng(test::sample_nc_int_vector());
        test::random_access_swappable(rng, *test::sample_nc_int_vector());
    }
    {
        test::nc_vector<int> rng(test::sample_ints());
        test::random_access_mutable(rng, test::sample_ints());
    }
}


void test_bidirectional()
{
    {
        test::nc_list<char> rng(test::sample_string());
        test::bidirectional_readable(rng, test::sample_string());
    }
    {
        test::nc_list<char> rng(test::sample_string());
        test::bidirectional_swappable(rng, test::sample_string());
    }
    {
        test::nc_list<char> rng(test::sample_string());
        test::bidirectional_mutable(rng, test::sample_string());
    }

    {
        test::nc_list<int> rng(test::sample_ints());
        test::bidirectional_readable(rng, test::sample_ints());
    }
    {
        boost::ptr_list<test::nc_int> rng(test::sample_nc_int_list());
        test::bidirectional_swappable(rng, *test::sample_nc_int_list());
    }
    {
        test::nc_list<int> rng(test::sample_ints());
        test::bidirectional_mutable(rng, test::sample_ints());
    }
}


void test_forward()
{
    {
        test::nc_slist<char> rng(test::sample_string());
        test::forward_readable(rng, test::sample_string());
    }
    {
        test::nc_slist<char> rng(test::sample_string());
        test::forward_swappable(rng, test::sample_string());
    }
    {
        test::nc_slist<char> rng(test::sample_string());
        test::forward_mutable(rng, test::sample_string());
    }

    {
        test::nc_slist<int> rng(test::sample_ints());
        test::forward_readable(rng, test::sample_ints());
    }
    {
        boost::ptr_list<test::nc_int> rng(test::sample_nc_int_list());
        test::forward_swappable(rng, *test::sample_nc_int_list());
    }
    {
        test::nc_slist<int> rng(test::sample_ints());
        test::forward_mutable(rng, test::sample_ints());
    }
}


void pstade_minimal_test()
{
    ::test_sort();
    ::test_equality();
    ::test_emptiness();
    ::test_random_access();
    ::test_bidirectional();
    ::test_forward();
}
