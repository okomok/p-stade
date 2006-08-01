#include <pstade/vodka/drink.hpp>
#include <boost/test/minimal.hpp>


// PStade.Oven
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/oven/break_into_range.hpp>


#include <string>
#include <vector>
#include <boost/range.hpp>
#include <pstade/oven/functions.hpp>


void test()
{
    using namespace pstade;
    using namespace oven;

    {
        int const offsets[] = { 2,2,4 };
        std::string src("12252001");
        std::vector<std::string> ans; {
            ans.push_back("12");
            ans.push_back("25");
            ans.push_back("2001");
        }

        BOOST_CHECK( oven::equals(
            ans,
            src|broken_into<std::string>(boost::offset_separator(offsets, offsets+3))
        ) );
    }
}


int test_main(int, char*[])
{
    ::test();
    return 0;
}
