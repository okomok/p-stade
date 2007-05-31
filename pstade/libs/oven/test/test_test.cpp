

// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/minimal_test.hpp>
#include <pstade/oven/test/bubble_sort.hpp>
#include <pstade/oven/test/comb_sort.hpp>
#include <pstade/oven/test/nclist.hpp>
#include <pstade/oven/test/ncslist.hpp>
#include <pstade/oven/test/ncstring.hpp>
#include <pstade/oven/test/ncvector.hpp>
#include <pstade/oven/test/equality.hpp>
#include <pstade/oven/test/emptiness.hpp>
#include <pstade/oven/test/random_access.hpp>
#include <pstade/oven/test/bidirectional.hpp>
#include <pstade/oven/test/forward.hpp>
#include <pstade/oven/test/single_pass.hpp>
#include <pstade/oven/test/sample_string.hpp>
#include <pstade/oven/test/sample_int_vector.hpp>
#include <pstade/oven/test/sample_int_list.hpp>
#include <pstade/oven/test/sample_int_slist.hpp>
#include <pstade/oven/test/sample_ncint_vector.hpp>
#include <pstade/oven/test/sample_ncint_list.hpp>
#include <pstade/oven/test/lightweight_proxy.hpp>


#include <utility> // pair
#include <pstade/oven/ptr_container.hpp>
#include <boost/ptr_container/ptr_list.hpp>
#include <boost/ptr_container/ptr_vector.hpp>
#include "./core.hpp"


namespace oven = pstade::oven;
using namespace oven;


void test_sort()
{
    {
        boost::ptr_vector<test::ncstring> vec;
        vec.push_back(new test::ncstring("c"));
        vec.push_back(new test::ncstring("a"));
        vec.push_back(new test::ncstring("d"));
        vec.push_back(new test::ncstring("b"));

        test::bubble_sort(vec);
        BOOST_CHECK( vec[0] == std::string("a") );
        BOOST_CHECK( vec[1] == std::string("b") );
        BOOST_CHECK( vec[2] == std::string("c") );
        BOOST_CHECK( vec[3] == std::string("d") );
    }
    {
        boost::ptr_vector<test::ncstring> vec;
        vec.push_back(new test::ncstring("c"));
        vec.push_back(new test::ncstring("a"));
        vec.push_back(new test::ncstring("d"));
        vec.push_back(new test::ncstring("b"));

        test::comb_sort(vec);
        BOOST_CHECK( vec[0] == std::string("a") );
        BOOST_CHECK( vec[1] == std::string("b") );
        BOOST_CHECK( vec[2] == std::string("c") );
        BOOST_CHECK( vec[3] == std::string("d") );
    }
    {
        boost::ptr_vector<test::ncstring> vec;
        vec.push_back(new test::ncstring("c"));
        vec.push_back(new test::ncstring("a"));
        vec.push_back(new test::ncstring("d"));
        vec.push_back(new test::ncstring("b"));

        test::selection_sort(vec);
        BOOST_CHECK( vec[0] == std::string("a") );
        BOOST_CHECK( vec[1] == std::string("b") );
        BOOST_CHECK( vec[2] == std::string("c") );
        BOOST_CHECK( vec[3] == std::string("d") );
    }
}


void test_equality()
{
    test::equality(*test::sample_string(), *test::sample_string());
    test::equality(*test::sample_int_vector(), *test::sample_int_vector());
}


void test_emptiness()
{
    test::ncvector<int> rng;
    test::emptiness(rng);
}


void test_lightweight_proxy()
{
    test::ncvector<int> rng;
    test::lightweight_proxy(std::make_pair(boost::begin(rng), boost::end(rng)));
    test::non_lightweight_proxy(rng);
}


void test_random_access()
{
    test::random_access_constant(*test::sample_string(), *test::sample_string());
    test::random_access_swappable(*test::sample_string(), *test::sample_string());
    test::random_access_constant(*test::sample_int_vector(), *test::sample_int_vector());
    test::random_access_swappable(*test::sample_ncint_vector(), *test::sample_ncint_vector());
}


void test_bidirectional()
{
    test::bidirectional_constant(*test::sample_int_list(), *test::sample_int_list());
    test::bidirectional_swappable(*test::sample_ncint_list(), *test::sample_ncint_list());
}


void test_forward()
{
    test::forward_constant(*test::sample_int_slist(), *test::sample_int_slist());
    test::forward_swappable(*test::sample_ncint_list(), *test::sample_ncint_list());
}


void test_single_pass()
{
    test::single_pass_readable(*test::sample_int_slist(), *test::sample_int_slist());
}


void pstade_minimal_test()
{
    ::test_sort();
    ::test_equality();
    ::test_emptiness();
    ::test_lightweight_proxy();
    ::test_random_access();
    ::test_bidirectional();
    ::test_forward();
    ::test_single_pass();
}
