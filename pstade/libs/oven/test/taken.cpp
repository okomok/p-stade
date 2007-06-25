#include "./prefix.hpp"
#include <pstade/vodka/drink.hpp>
#include <boost/test/minimal.hpp>


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include "./detail/v1_tests.hpp"
#include <pstade/oven/taken.hpp>


#include <string>
#include "./detail/v1_core.hpp"
#include <pstade/oven/identities.hpp>


void test()
{
    namespace oven = pstade::oven;
    using namespace oven;

    {
        std::string rng("hello, take_range!");
        std::vector<char> expected = std::string("hello")|copied;

        BOOST_CHECK( oven::test_Forward_Readable_Writable(
            rng|identities(in_forward)|taken(5),
            expected
        ) );

        BOOST_CHECK( oven::test_Forward_Readable_Writable(
            rng|taken(5000)|taken(5),
            expected
        ) );
    }
    {
        std::string rng("hello, take_range!");
        std::vector<char> expected = rng|copied;

        BOOST_CHECK( oven::test_Forward_Readable_Writable(
            rng|taken(rng.size()),
            expected
        ) );
    }
    {
        std::string rng("hello, take_range!");
        std::vector<char> expected = rng|copied;

        BOOST_CHECK( oven::test_Forward_Readable_Writable(
            rng|identities(in_forward)|taken(5000),
            expected
        ) );
    }
    {
        std::string rng("hello, take_range!");

        BOOST_CHECK( oven::test_empty(
            rng|taken(0)
        ) );

        BOOST_CHECK( oven::test_empty(
            rng|identities(in_forward)|taken(0)
        ) );
    }
}


int test_main(int, char*[])
{
    ::test();
    return 0;
}
