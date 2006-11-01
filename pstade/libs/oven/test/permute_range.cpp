#include <pstade/vodka/drink.hpp>
#include <boost/test/minimal.hpp>


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/oven/tests.hpp>
#include <pstade/oven/permute_range.hpp>


#include <iostream>
#include <string>
#include <pstade/oven/functions.hpp>
#include <pstade/oven/counting_range.hpp>
#include <pstade/oven/reverse_range.hpp>


void test()
{
    namespace oven = pstade::oven;
    using namespace oven;

    {
        int rng[] = { 0,1,2,3,4,5,6,7,8,9 };
        int ans[] = { 8,6,2,3 };
        std::vector<int> expected = ans|copied;
        int ind[] = { 8, 6, 2, 3 };

        oven::copy(rng|permuted(ind)|reversed, oven::to_stream(std::cout));
        BOOST_CHECK( oven::test_RandomAccess_Readable_Writable(
            rng|permuted(ind),
            expected
        ) );

        // 'permute_iterator' can work with 'counting_iterator'
        // which manage reference by itself.
        BOOST_CHECK( oven::test_RandomAccess_Readable(
            oven::count_to(10)|permuted(ind),
            expected
        ) );
    }
    {
        std::string src("0123456789");
        std::string ans("8623");
        int ind[] = { 8, 6, 2, 3 };

        BOOST_CHECK( oven::equals( src|permuted(ind), ans ) );
    }
}


int test_main(int, char*[])
{
    ::test();
    return 0;
}
