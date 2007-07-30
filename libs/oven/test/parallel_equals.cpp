#include "./prefix.hpp"

// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/oven/parallel_equals.hpp>
#include <pstade/unit_test.hpp>


bool int_equal(int x, int y)
{
    return x == y;
}


void pstade_unit_test()
{
    namespace oven = pstade::oven;
    using namespace oven;

    {
        int a[] = { 1,2,13,6,1,3,4,16,3,1,7,4,2,1,7,4,2,1,3,5,1 };
        int b[] = { 1,2,13,6,1,3,4,16,3,1,7,4,2,1,7,4,2,1,3,5,1 };
        BOOST_CHECK( parallel_equals(3, a, b) );
        BOOST_CHECK( parallel_equals(3, a, b, &::int_equal) );
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
}
