#include "./prefix.hpp"
#include <pstade/vodka/drink.hpp>


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/oven/stream_lines.hpp>
#include <boost/test/minimal.hpp>
#include "./detail/v1_tests.hpp"


#include <iterator>
#include <sstream>
#include <string>
#include "./detail/v1_core.hpp"
#include <pstade/oven/copied.hpp>
#include <vector>


namespace oven = pstade::oven;
using namespace oven;


void test_line()
{
    {
        std::string src("hello\nistream\nrange\n!");
        std::stringstream ss;
        ss << src;
        std::vector<std::string> expected; {
            expected.push_back("hello");
            expected.push_back("istream");
            expected.push_back("range");
            expected.push_back("!");
        }
        BOOST_CHECK( oven::test_SinglePass_Readable(
            oven::stream_lines(ss),
            expected
        ) );
    }
}


int test_main(int, char*[])
{
    ::test_line();
    return 0;
}
