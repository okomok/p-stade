#include "./prelude.hpp"
#include <pstade/vodka/drink.hpp>


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/unit_test.hpp>


#include "./detail/test.hpp"
#include <pstade/oven/ptr_container.hpp>


#include <utility> // pair


namespace oven = pstade::oven;
using namespace oven;


void test_equality()
{
    int b[] = { 1,2,3,4,5,6,7,8 };
    int a[] = { 1,2,3,4,5,6,7,8 };
    test::equality(b, a);
}


void test_new()
{
    int c[] = { 1,2,3,4,5 };
    test::random_access_swappable(*test::new_vector<test::ncint>(c), *test::new_vector<test::ncint>(c));
    test::bidirectional_swappable(*test::new_list<test::ncint>(c), *test::new_list<test::ncint>(c));
}


void test_emptiness()
{
    test::emptiness(*test::new_vector0<int>());
    test::emptiness(*test::new_list0<int>());
}


void test_lightweight_copyable()
{
    int c[] = { 1,2,3,4,5 };
    test::lightweight_copyable(std::make_pair(boost::begin(c), boost::end(c)));
    test::non_lightweight_copyable(*test::new_vector<test::ncint>(c));
}


template< class Range, class RangeA >
void test_comb_sort(Range& rng, RangeA const& rngA)
{
    test::comb_sort(rng);
    test::equality(rng, rngA);
}

template< class Range, class RangeA >
void test_bubble_sort(Range& rng, RangeA const& rngA)
{
    test::bubble_sort(rng);
    test::equality(rng, rngA);
}

template< class Range, class RangeA >
void test_selection_sort(Range& rng, RangeA const& rngA)
{
    test::bubble_sort(rng);
    test::equality(rng, rngA);
}


void test_sort()
{
    {
        int c[] = { 4,5,1,2,1,7,1,4,6,2,3 };
        int a[] = { 1,1,1,2,2,3,4,4,5,6,7 };
        ::test_comb_sort(*test::new_vector<test::ncint>(c), a);
    }
    {
        int c[] = { 4,5,1,2,1,7,1,4,6,2,3 };
        int a[] = { 1,1,1,2,2,3,4,4,5,6,7 };
        ::test_bubble_sort(*test::new_list<test::ncint>(c), a);
    }
    {
        int c[] = { 4,5,1,2,1,7,1,4,6,2,3 };
        int a[] = { 1,1,1,2,2,3,4,4,5,6,7 };
        ::test_selection_sort(*test::new_list<test::ncint>(c), a);
    }
}


void test_random_access()
{
    int c[] = { 4,5,1,2,1,7,1,4,6,2,3 };
    test::random_access_constant(*test::new_vector<int>(c), c);
    test::random_access_swappable(*test::new_vector<int>(c), c);
    test::random_access_swappable(*test::new_vector<test::ncint>(c), *test::new_vector<test::ncint>(c));
}


void test_bidirectional()
{
    int c[] = { 4,5,1,2,1,7,1,4,6,2,3 };
    test::bidirectional_constant(*test::new_list<int>(c), c);
    test::bidirectional_swappable(*test::new_list<int>(c), c);
    test::bidirectional_swappable(*test::new_list<test::ncint>(c), *test::new_list<test::ncint>(c));
}


void test_forward()
{
    int c[] = { 4,5,1,2,1,7,1,4,6,2,3 };
    test::forward_constant(*test::new_list<int>(c), c);
    test::forward_swappable(*test::new_list<int>(c), c);
    test::forward_swappable(*test::new_list<test::ncint>(c), *test::new_list<test::ncint>(c));
}


void test_single_pass()
{
    int c[] = { 4,5,1,2,1,7,1,4,6,2,3 };
    test::single_pass_readable(*test::new_list<int>(c), c);
}


void test_proxies()
{
    int c[] = { 4,5,1,2,1,7,1,4,6,2,3 };
    test::random_access_swappable(c|test::proxies, c);
}


void pstade_unit_test()
{
    ::test_equality();
    ::test_new();
    ::test_emptiness();
    ::test_lightweight_copyable();
    ::test_sort();

    ::test_random_access();
    ::test_bidirectional();
    ::test_forward();
    ::test_single_pass();
    ::test_proxies();
}
