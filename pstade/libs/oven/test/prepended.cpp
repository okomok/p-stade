#include <pstade/vodka/drink.hpp>
#include <boost/test/minimal.hpp>


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/oven/tests.hpp>
#include <pstade/oven/prepended.hpp>


#include <string>
#include <vector>
#include <pstade/oven/functions.hpp>
#include <pstade/oven/single.hpp>


void test()
{
    namespace oven = pstade::oven;
    using namespace oven;

    {
        int src0[] = { 1,6,9 };
        int src1   = 8;
        int src2   = 2;
        int src3   = 5;
        int ans[]  = { 5,2,8,1,6,9 };

        std::vector<int> expected = ans|copied;
        BOOST_CHECK( oven::test_RandomAccess_Readable_Writable(
            src0|prepended(src1)|prepended(src2)|prepended(src3),
            expected
        ) );
    }

    const std::string src("bcde"); // constant
    std::string ans("abcde");

    {
        std::string src("bcde"); // mutable
        char ch = 'a'; // mutable
        BOOST_CHECK( oven::equals(oven::make_prepended(src, ch), ans) );
    }

    {
        BOOST_CHECK( oven::equals(src|prepended('a'), ans) );

        std::cout << std::endl;
        const char ch = 'a';
        BOOST_FOREACH(char c, src|prepended(ch)) {
            std::cout << c;
        }
        std::cout << std::endl;
    }

    {
        BOOST_CHECK( oven::equals(
            std::string("de")|
                prepended('c')|prepended('b')|prepended('a'),
            ans)
        );
    }
}


int test_main(int, char*[])
{
    ::test();
    return 0;
}
