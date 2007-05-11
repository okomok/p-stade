#include <pstade/vodka/drink.hpp>
#include <boost/test/minimal.hpp>


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/oven/tests.hpp>
#include <pstade/oven/adjacent_filtered.hpp>


#include <vector>
#include "./core.hpp"
#include <pstade/oven/identities.hpp>
#include <pstade/oven/regular.hpp>
#include <boost/lambda/core.hpp>
#include <boost/lambda/lambda.hpp>


struct is_divisor
{
    bool operator()(int x, int y) const
    { return (y % x) == 0; }
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
        int ans[] = { 2, 2, 4, 4, 8, 8, 40, 80 };
        std::vector<int> expected = ans|copied;

        BOOST_CHECK( oven::test_Forward_Readable(
            src|adjacent_filtered(::is_divisor()),
            expected
        ) );

        BOOST_CHECK( oven::test_Forward_Readable(
            oven::make_adjacent_filtered(src, ::is_divisor()),
            expected
        ) );

        BOOST_CHECK( oven::test_SinglePass_Readable(
            src|identities(in_single_pass)|adjacent_filtered(::is_divisor()),
            expected
        ) );
    }
    {
        int ans[] = { 2, 4, 6, 8, 10, 20, 40, 80, 120 };
        std::vector<int> expected = ans|copied;

        BOOST_CHECK( oven::test_Forward_Readable(
            src|adjacent_filtered(::not_equal_to()),
            expected
        ) );

        namespace lambda = boost::lambda;
        BOOST_CHECK( oven::test_Forward_Readable(
            src|adjacent_filtered(regular(lambda::_1 != lambda::_2)),
            expected
        ) );
    }
}


int test_main(int, char*[])
{
    ::test();
    return 0;
}
