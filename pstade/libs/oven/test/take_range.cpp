#include <pstade/vodka/drink.hpp>
#include <boost/test/minimal.hpp>


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/oven/tests.hpp>
#include <pstade/oven/take_range.hpp>


#include <string>
#include <boost/range.hpp>
#include <pstade/oven/functions.hpp>


void test()
{
    namespace oven = pstade::oven;
    using namespace oven;

    {
        std::string rng("hello, take_range!");
        std::vector<char> expected = std::string("hello")|copied;

        BOOST_CHECK( oven::test_RandomAccess_Readable_Writable(
            rng|taken(7)|taken(5),
            expected
        ) );
    }
    {
        std::string src("hello, take_range!");
        std::string ans("hello");
        BOOST_CHECK( oven::equals(src|taken(7)|taken(5), ans) );
    }
}


int test_main(int, char*[])
{
    ::test();
    return 0;
}
