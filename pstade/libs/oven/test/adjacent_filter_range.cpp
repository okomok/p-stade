#include <pstade/vodka/drink.hpp>
#include <boost/test/minimal.hpp>


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/oven/tests.hpp>
#include <pstade/oven/adjacent_filter_range.hpp>


#include <vector>
#include <pstade/oven/functions.hpp>


struct is_not_divisor
{
    bool operator()(int x, int y) const
    { return (y % x) != 0; }
};


struct not_equal_to
{
    bool operator()(int x, int y) const
    { return x != y; }
};


void test()
{
    namespace oven = pstade::oven;
    using namespace oven;

    int const src[] = { 2, 2, 4, 4, 6, 8, 8, 10, 10, 20, 40, 80, 120 };

    {
        int ans[] = { 2, 6, 8, 10, 120 };
        std::vector<int> expected = ans|copied;

        BOOST_CHECK( oven::test_Bidirectional_Readable(
            src|adjacent_filtered(is_not_divisor()),
            expected
        ) );
    }
    {
        int ans[] = { 2, 4, 6, 8, 10, 20, 40, 80, 120 };
        std::vector<int> expected = ans|copied;

        BOOST_CHECK( oven::test_Bidirectional_Readable(
            src|adjacent_filtered(not_equal_to()),
            expected
        ) );
    }
    {
        int ans[] = { 2, 8, 10 };
        std::vector<int> expected = ans|copied;

        BOOST_CHECK( oven::test_Bidirectional_Readable(
            src|adjacent_filtered(is_not_divisor())|adjacent_filtered(is_not_divisor()),
            expected
        ) );
    }
}


int test_main(int, char*[])
{
    ::test();
    return 0;
}
