#include <pstade/vodka/drink.hpp>
#include <boost/test/minimal.hpp>


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/oven/tests.hpp>
#include <pstade/oven/stream_input.hpp>


#include <sstream>
#include <string>
#include <pstade/oven/functions.hpp>


void test()
{
    namespace oven = pstade::oven;
    using namespace oven;

    std::string answer("hello,istreambuf_range!");

    {
        std::stringstream ss;
        ss << answer;
        std::vector<char> expected = answer|copied;

        BOOST_CHECK( oven::test_SinglePass_Readable(
            oven::streambuf_input(ss),
            expected
        ) );
    }

    {
        std::stringstream ss;
        ss << answer;
        std::string result = oven::streambuf_input(ss)|copied;
        BOOST_CHECK( oven::equals(result, answer) );
    }

    {
        std::stringstream ss;
        ss << answer;
        std::string result = oven::streambuf_input(ss.rdbuf())|copied;
        BOOST_CHECK( oven::equals(result, answer) );
    }
}


int test_main(int, char*[])
{
    ::test();
    return 0;
}
