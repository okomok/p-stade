#include <pstade/vodka/drink.hpp>
#define PSTADE_CONCEPT_CHECK


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#define PSTADE_OVEN_TEST_DO_ITER_SWAP
#include <pstade/oven/do_iter_swap.hpp>
#include <pstade/minimal_test.hpp>


#include "./detail/proxies.hpp"
#include <boost/range/begin.hpp>
#include <boost/noncopyable.hpp>
#include <vector>


namespace oven = pstade::oven;
using namespace oven;


bool g_swap_called = false;


namespace my {

    struct A
    {
        A(int i) : impl(i) { }
        int impl;    
    };

    void swap(A& l, A& r)
    {
        std::swap(l.impl, r.impl);
        g_swap_called = true;
    }
}


template< class R1, class R2 >
void swap_front(R1& r1, R2& r2)
{
    do_iter_swap(boost::begin(r1), boost::begin(r2));
};


void pstade_minimal_test()
{
    {
        int r1[] = { 0,1,2,3 };
        int r2[] = { 1,2,3,4,5 };
        ::swap_front(r1, r2);
        BOOST_CHECK(r1[0] == 1);
        BOOST_CHECK(r2[0] == 0);
    }
    {
        // iter_swap customization check
        int r1[] = { 0,1,2,3 };
        int r2[] = { 1,2,3,4,5 };
        ::swap_front(r1|test::proxies, r2|test::proxies);
        BOOST_CHECK(r1[0] == 1);
        BOOST_CHECK(r2[0] == 0);
    }
    {
        // swap customization check
        std::vector< ::my::A > r1;
        r1.push_back(0); r1.push_back(1);
        std::vector< ::my::A > r2;
        r2.push_back(1); r2.push_back(2);
        ::swap_front(r1, r2);
        BOOST_CHECK(g_swap_called);
        BOOST_CHECK(r1[0].impl == 1);
        BOOST_CHECK(r2[0].impl == 0);
    }
}
