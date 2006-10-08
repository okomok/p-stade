#include <pstade/vodka/drink.hpp>
#include <boost/test/minimal.hpp>


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/oven/tests.hpp>
#include <pstade/oven/concatenate_range.hpp>


#include <vector>
#include <string>
#include <pstade/oven/functions.hpp>
#include <pstade/oven/reverse_range.hpp>


void test()
{
    namespace oven = pstade::oven;
    using namespace oven;

    std::vector<std::string> rng; {
        rng.push_back("abcd");
        rng.push_back("efg");
        rng.push_back("h");
        rng.push_back("");
        rng.push_back("ij");
        rng.push_back("");
        rng.push_back("klmn");
        rng.push_back("");
    }

    {
        std::vector<char> expected = std::string("abcdefghijklmn")|copied;
        BOOST_CHECK( oven::test_Bidirectional_Readable_Writable(rng|concatenated, expected) );
    }
    {
        std::vector<char> expected = std::string("nmlkjihgfedcba")|copied;
        BOOST_CHECK( oven::test_Bidirectional_Readable_Writable(rng|concatenated|reversed, expected) );
    }
    {
        std::vector<std::string> rng;
        rng.push_back("");
        rng.push_back("");
        rng.push_back("");
        BOOST_CHECK( oven::test_empty(rng|concatenated) );
        rng.push_back("ABC");
        std::vector<char> expected = std::string("ABC")|copied;
        BOOST_CHECK( oven::test_Bidirectional_Readable_Writable(rng|concatenated, expected) );
        rng.push_back("");
        rng.push_back("");
        BOOST_CHECK( oven::test_Bidirectional_Readable_Writable(rng|concatenated, expected) );
    }   
}


int test_main(int, char*[])
{
    ::test();
    return 0;
}
