#include <pstade/vodka/drink.hpp>
#include <boost/test/minimal.hpp>


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/oven/tests.hpp>
#include <pstade/oven/lower_chars.hpp>
#include <pstade/oven/upper_chars.hpp>
#include <pstade/oven/const_refs.hpp>


#include <string>
#include "./core.hpp"


void test()
{
    namespace oven = pstade::oven;
    using namespace oven;

    {
        std::string ans("abcdefg");
        std::vector<char> expected = ans|copied;

        BOOST_CHECK( oven::test_RandomAccess_Readable(
            std::string("AbCdEFg")|lower_chars|const_refs,
            expected
        ) );
    }
    {
        std::string ans("ABCDEFG");
        std::vector<char> expected = ans|copied;

        BOOST_CHECK( oven::test_RandomAccess_Readable(
            std::string("AbCdEFg")|upper_chars|const_refs,
            expected
        ) );
    }

    {
        BOOST_CHECK( equals(
            std::string("AbCdEFG")|lower_chars,
            std::string("abcdefg")
        ) );
    }
    {
        BOOST_CHECK( equals(
            std::string("AbCdEFG")|lower_chars(std::locale()),
            std::string("abcdefg")
        ) );
    }
    {
        BOOST_CHECK( equals(
            std::string("AbCdEFG")|upper_chars,
            std::string("ABCDEFG")
        ) );
    }
    {
        BOOST_CHECK( equals(
            std::string("AbCdEFG")|upper_chars(std::locale()),
            std::string("ABCDEFG")
        ) );
    }
}


int test_main(int, char*[])
{
    ::test();
    return 0;
}
