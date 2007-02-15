#include <pstade/vodka/drink.hpp>
#include <boost/test/minimal.hpp>


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/oven/tests.hpp>
#include <pstade/oven/detail/indexed_deque.hpp>


namespace oven = pstade::oven;
using namespace oven;


void test()
{
    {
        typedef detail::indexed_deque<int> deque_t;
        deque_t dq;

        dq.positive_push(0);
        dq.positive_push(10);
        dq.negative_push(-10);
        dq.positive_push(20);
        dq.negative_push(-20);
        dq.positive_push(30);
        dq.positive_push(40);
        dq.negative_push(-30);

        BOOST_CHECK( !dq.is_in_range(5) );
        BOOST_CHECK( !dq.is_in_range(-4) );

        for (deque_t::index_type i = -3; i <= 4; ++i) {
            BOOST_CHECK(dq[i] == i * 10);
        }
    }
}


int test_main(int, char*[])
{
    ::test();
    return 0;
}
