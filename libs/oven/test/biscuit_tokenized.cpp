#include <pstade/vodka/drink.hpp>
#include <boost/test/minimal.hpp>


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/oven/tests.hpp>
#include <pstade/oven/biscuit_tokenized.hpp>


#include "./core.hpp"
#include <string>
#include <pstade/oven/concatenated.hpp>
#include <pstade/biscuit/parser.hpp>


void test()
{
    namespace biscuit = pstade::biscuit;
    namespace oven = pstade::oven;
    using namespace oven;

    {
        std::string input("This is his face");

        std::vector<char> expected_ = std::string("Thisishisface")|copied;
        BOOST_CHECK( oven::test_Forward_Readable(
            input|biscuit_tokenized(biscuit::plus<biscuit::alnum_com>())|concatenated,
            expected_
        ) );
    }
}


int test_main(int, char*[])
{
    ::test();
    return 0;
}
