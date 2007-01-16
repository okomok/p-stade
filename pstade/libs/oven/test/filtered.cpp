#include <pstade/vodka/drink.hpp>
#include <boost/test/minimal.hpp>


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/oven/tests.hpp>
#include <pstade/oven/filtered.hpp>


#include <vector>
#include <boost/foreach.hpp>
#include <boost/range.hpp>
#include <pstade/oven/functions.hpp>


struct is_positive
{
    bool operator()(int x) const
    { return 0 < x; }
};


struct is_even
{
    bool operator()(int x) const
    { return (x % 2) == 0; }
};


void test()
{
    namespace oven = pstade::oven;
    using namespace oven;

    int rng[] = { 0, -1, 4, -3, 5, 8, -2, 10 };
    {
        int ans[] = { 4, 5, 8, 10 };
        std::vector<int> expected = ans|copied;
        BOOST_CHECK( oven::test_Bidirectional_Readable_Writable(
            oven::make_filtered(rng, ::is_positive()),
            expected
        ) );
    }
    {
        int ans[] = { 4, 8, 10 };
        std::vector<int> expected = ans|copied;
        BOOST_CHECK( oven::test_Bidirectional_Readable_Writable(
                rng |
                    oven::filtered(::is_positive()) |
                    oven::filtered(::is_even()),
                expected
        ) );
    }
}


int test_main(int, char*[])
{
    ::test();
    return 0;
}
