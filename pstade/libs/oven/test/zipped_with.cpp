#include <pstade/vodka/drink.hpp>
#include <boost/test/minimal.hpp>


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/oven/tests.hpp>
#include <pstade/oven/zipped_with.hpp>


#include <string>
#include <vector>
#include <boost/foreach.hpp>
#include <boost/range.hpp>
#include <pstade/oven/functions.hpp>
#include <pstade/pack.hpp>


int plus2(int x, int y)
{
    return x + y;
}

int plus3(int x, int y, int z)
{
    return x + y + z;
}


void test()
{
    namespace oven = pstade::oven;
    using namespace oven;

    {
        int xs[]  = { 0, 1, 2, 3, 4, 5, 6 };
        int ys[]  = { 1, 6, 1, 2, 7, 8, 3 };
        int ans[] = { 1, 7, 3, 5,11,13, 9 };
        std::vector<int> expected = ans|copied;

       BOOST_CHECK( oven::test_RandomAccess_Readable(
            xs|pstade::packed(ys)|zipped_with(&::plus2),
            expected
        ) );
    }

    {
        int xs[]  = { 0, 1, 2, 3, 4, 5, 6 };
        int ys[]  = { 1, 6, 1, 2, 7, 8, 3 };
        int ans[] = { 1, 7, 3, 5,11,13, 9 };

        BOOST_CHECK( oven::equals(
            boost::tie(xs, ys)|zipped_with(&::plus2),
            ans
        ) );
    }

    {
        int xs[]  = { 0, 1, 2, 3, 4, 5, 6 };
        int ys[]  = { 1, 6, 1, 2, 7, 8, 3 };
        int zs[]  = { 2, 1, 5, 1, 6, 7, 4 };
        int ans[] = { 3, 8, 8, 6,17,20,13 };

        BOOST_CHECK( oven::equals(
            boost::tie(xs, ys, zs)|zipped_with(&::plus3),
            ans
        ) );
    }
    
}


int test_main(int, char*[])
{
    ::test();
    return 0;
}
