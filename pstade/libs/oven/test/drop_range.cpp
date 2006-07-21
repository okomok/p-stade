#include <pstade/vodka/drink.hpp>
#include <boost/test/minimal.hpp>


// PStade.Oven
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/oven/drop_range.hpp>


#include <string>
#include <boost/range.hpp>
#include <pstade/oven/functions.hpp>


void test()
{
    using namespace pstade;
    using namespace oven;

    {
        std::string src("hello, drop_range!");
        std::string ans("range!");
        BOOST_CHECK( oven::equals(src|dropped(7)|dropped(5), ans) );
    }
}


int test_main(int, char*[])
{
    ::test();
    return 0;
}
