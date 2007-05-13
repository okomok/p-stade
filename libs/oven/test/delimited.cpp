#include <pstade/vodka/drink.hpp>
#include <boost/test/minimal.hpp>


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/oven/tests.hpp>
#include <pstade/oven/delimited.hpp>


#include <string>
#include "./core.hpp"
#include <pstade/oven/dropped.hpp>
#include <pstade/oven/as_literal.hpp>
#include <pstade/oven/single.hpp>
#include <pstade/oven/transformed.hpp>
#include <pstade/biscuit/parser.hpp>
#include <pstade/biscuit/range/token_range.hpp>


void test()
{
    namespace oven = pstade::oven;
    namespace biscuit = pstade::biscuit;
    using namespace oven;

    {
        std::string delim("xyz");
        std::string src("12345678");

        std::vector<char> expected = std::string("xyz12xyz34xyz56xyz78")|copied;

        BOOST_CHECK( oven::test_Forward_Readable(
            src|biscuit::tokenized< biscuit::seq<biscuit::any, biscuit::any> >()|delimited(delim),
            expected
        ) );
    }
    {
        BOOST_CHECK( equals(
            std::string("abcde")|biscuit::tokenized<biscuit::any>()|
                delimited("--"|as_literal)|dropped(2),
            std::string("a--b--c--d--e")
        ) );
    }
    {
        BOOST_CHECK( equals(
            std::string("abcde")|transformed(single)|
                delimited("--"|as_literal)|dropped(2),
            std::string("a--b--c--d--e")
        ) );
    }
}


int test_main(int, char*[])
{
    ::test();
    return 0;
}
