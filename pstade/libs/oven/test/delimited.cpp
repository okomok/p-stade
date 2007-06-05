#include "./prelude.hpp"
#include <pstade/vodka/drink.hpp>
#define PSTADE_CONCEPT_CHECK


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/oven/delimited.hpp>
#include <pstade/minimal_test.hpp>
#include "./detail/test.hpp"


#include <string>
#include <pstade/oven/equals.hpp>
#include <pstade/oven/dropped.hpp>
#include <pstade/oven/as_literal.hpp>
#include <pstade/oven/single.hpp>
#include <pstade/oven/transformed.hpp>
#include <pstade/oven/copy_range.hpp>
#include <pstade/biscuit/parser.hpp>
#include <pstade/biscuit/range/token_range.hpp>


void pstade_minimal_test()
{
    namespace oven = pstade::oven;
    namespace biscuit = pstade::biscuit;
    using namespace oven;

    {
        std::string delim("xyz");
        std::string src("12345678");

        std::vector<char> expected = std::string("xyz12xyz34xyz56xyz78")|copied;

        test::forward_constant(
            src|biscuit::tokenized< biscuit::seq<biscuit::any, biscuit::any> >()|delimited(delim),
            expected
        );
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
