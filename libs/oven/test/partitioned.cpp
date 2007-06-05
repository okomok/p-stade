#include "./prelude.hpp"
#include <pstade/vodka/drink.hpp>
#include <boost/test/minimal.hpp>


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include "./detail/v1_tests.hpp"
#include <pstade/oven/partitioned.hpp>


#include "./detail/v1_core.hpp"


bool is_even(int x)
{
    return x % 2 == 0;
}


void test()
{
    namespace oven = pstade::oven;
    using namespace oven;

    {
        int rng[] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16};
        int ans0[] = {2,4,6,8,10,12,14,16};
        int ans1[] = {1,3,5,7,9,11,13,15};
        std::vector<int> expected0 = ans0|copied;
        std::vector<int> expected1 = ans1|copied;

        BOOST_CHECK( oven::test_Bidirectional_Readable_Writable(
            (rng|partitioned(&is_even)).first,
            expected0
        ) );

        BOOST_CHECK( oven::test_Bidirectional_Readable_Writable(
            (rng|partitioned(&is_even)).second,
            expected1
        ) );
    }
}


int test_main(int, char*[])
{
    ::test();
    return 0;
}
