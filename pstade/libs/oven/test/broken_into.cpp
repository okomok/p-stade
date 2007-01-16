#include <pstade/vodka/drink.hpp>
#include <boost/test/minimal.hpp>


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/oven/tests.hpp>
#include <pstade/oven/broken_into.hpp>


#include <string>
#include <vector>
#include <pstade/oven/functions.hpp>


void test()
{
    namespace oven = pstade::oven;
    using namespace oven;

    {
        int const offsets[] = { 2,2,4 };
        std::string src("12252001");
        std::vector<std::string> expected; {
            expected.push_back("12");
            expected.push_back("25");
            expected.push_back("2001");
        }

        BOOST_CHECK( oven::test_Forward_Readable(
            src|broken_into<std::string>(boost::offset_separator(offsets, offsets+3)),
            expected
        ) );
    }
}


int test_main(int, char*[])
{
    ::test();
    return 0;
}
