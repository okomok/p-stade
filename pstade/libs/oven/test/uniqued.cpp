#include <pstade/vodka/drink.hpp>
#include <boost/test/minimal.hpp>


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/oven/tests.hpp>
#include <pstade/oven/uniqued.hpp>


#include <pstade/oven/functions.hpp>


void test()
{
    namespace oven = pstade::oven;
    using namespace oven;

    {
        int rng[] = {1,3,3,2,2,1};
        int ans[] = {1,3,2,1};
        std::vector<int> expected = ans|copied;

        BOOST_CHECK( oven::test_Forward_Readable(
            rng|uniqued,
            expected
        ) );
    }

    {
        int rng[] = {3,3,2,2,1,1};
        int ans[] = {3,2,1};
        std::vector<int> expected = ans|copied;

        BOOST_CHECK( oven::test_Forward_Readable(
            rng|uniqued,
            expected
        ) );
    }
}


int test_main(int, char*[])
{
    ::test();
    return 0;
}
