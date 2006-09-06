#include <pstade/vodka/drink.hpp>
#include <boost/test/minimal.hpp>


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/oven/istreambuf_range.hpp>


#include <sstream>
#include <string>
#include <pstade/oven/functions.hpp>


void test()
{
    using namespace pstade;
    using namespace oven;

    std::string answer("hello,istreambuf_range!");

    {
        std::stringstream ss;
        ss << answer;
        std::string result = oven::make_istreambuf_range(ss)|copied;
        BOOST_CHECK( oven::equals(result, answer) );
    }

    {
        std::stringstream ss;
        ss << answer;
        std::string result = oven::make_istreambuf_range(ss.rdbuf())|copied;
        BOOST_CHECK( oven::equals(result, answer) );
    }
}


int test_main(int, char*[])
{
    ::test();
    return 0;
}
