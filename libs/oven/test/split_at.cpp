#include <pstade/vodka/drink.hpp>
#include <boost/test/minimal.hpp>


// Boost.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include "./detail/v1_tests.hpp"
#include <pstade/oven/split_at.hpp>


#include <string>
#include "./detail/v1_core.hpp"


void test()
{
    namespace oven = pstade::oven;
    using namespace oven;

    {
        int rng[] = {0,2,4,8,6,10,3,5,2,5,6,1};
        int ans0[] = {0,2,4,8,6,10};
        int ans1[] = {3,5,2,5,6,1};
        std::vector<int> expected0 = ans0|copied;
        std::vector<int> expected1 = ans1|copied;

        BOOST_CHECK( oven::test_RandomAccess_Readable_Writable(
            (rng|split_at(6)).first,
            expected0
        ) );

        BOOST_CHECK( oven::test_RandomAccess_Readable_Writable(
            (rng|split_at(6)).second,
            expected1
        ) );
    }
}


int test_main(int, char*[])
{
    ::test();
    return 0;
}
