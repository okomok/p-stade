#include "./prefix.hpp"
#include <pstade/vodka/drink.hpp>
#define PSTADE_CONCEPT_CHECK


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/oven/biscuit_tokenized.hpp>
#include <pstade/minimal_test.hpp>
#include "./detail/test.hpp"


#include <string>
#include <pstade/oven/concatenated.hpp>
#include <pstade/oven/copied.hpp>
#include <pstade/biscuit/parser.hpp>


void pstade_minimal_test()
{
    namespace biscuit = pstade::biscuit;
    namespace oven = pstade::oven;
    using namespace oven;

    {
        std::string b("This is his face");

        std::vector<char> a = std::string("Thisishisface")|copied;
        test::forward_constant(b|biscuit_tokenized(biscuit::plus<biscuit::alnum_com>())|concatenated, a);
        test::forward_constant(b|const_refs|biscuit_tokenized(biscuit::plus<biscuit::alnum_com>())|concatenated, a);
    }
}
