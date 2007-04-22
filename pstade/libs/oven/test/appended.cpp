#include <pstade/vodka/drink.hpp>
#include <boost/test/minimal.hpp>


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/oven/tests.hpp>
#include <pstade/oven/appended.hpp>


#include <string>
#include <vector>
#include "./core.hpp"
#include <pstade/oven/as_single.hpp>


void test()
{
    namespace oven = pstade::oven;
    using namespace oven;

    {
        int src0[] = { 1,6,9 };
        int src1   = 8;
        int src2   = 2;
        int src3   = 5;
        int ans[]  = { 1,6,9,8,2,5 };

        std::vector<int> expected = ans|copied;
        BOOST_CHECK( oven::test_RandomAccess_Readable_Writable(
            src0|appended(src1)|appended(src2)|appended(src3),
            expected
        ) );
    }

    std::string const src("abcd");
    std::string ans("abcde");
#if 0 // no longer a public class template
    {
        std::string src("abcd");
        char ch = 'e';
        append_range<std::string, char> rng(src, ch);
        BOOST_CHECK( oven::equals(rng, ans) );
    }
#endif
    {
        std::string src("abcd"); // mutable
        char ch = 'e'; // mutable
        BOOST_CHECK( oven::equals(oven::make_appended(src, ch), ans) );
    }

    {
        BOOST_CHECK( oven::equals(src|appended('e'), ans) );

        std::cout << std::endl;
        char ch = 'e';
        BOOST_FOREACH(char c, src|appended(ch)) {
            std::cout << c;
        }
        std::cout << std::endl;
    }

    {
        BOOST_CHECK( oven::equals(
            std::string("ab")|
                appended('c')|appended('d')|appended('e'),
            ans)
        );
    }
}


int test_main(int, char*[])
{
    ::test();
    return 0;
}
