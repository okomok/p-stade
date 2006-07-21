#include <pstade/vodka/drink.hpp>
#include <boost/test/minimal.hpp>


// PStade.Oven
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/oven/accumulate_range.hpp>


#include <iterator>
#include <string>
#include <vector>
#include <boost/range.hpp>
#include <pstade/oven/functions.hpp>


int minus(int state, int x)
{
    return state - x;
}

void test()
{
    using namespace pstade;
    using namespace oven;

    {
        int src[]  = { 1, 2, 3, 4, 5, 6, 7, 8, 9,10};
        int ans1[] = { 1, 3, 6,10,15,21,28,36,45,55};

        BOOST_CHECK( oven::equals(
            src|accumulated(0),
            ans1
        ) );
    }

    {
        int src[] = { 1, 2, 3, 4 };
        int ans[] = { 9, 7, 4, 0 }; 

        BOOST_CHECK( oven::equals(
            src|accumulated(10, ::minus),
            ans
        ) );

        BOOST_CHECK( oven::equals(
            src|accumulated(10, &::minus),
            ans
        ) );
    }
}


int test_main(int, char*[])
{
    ::test();
    return 0;
}
