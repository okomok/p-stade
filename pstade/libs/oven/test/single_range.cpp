#include <pstade/vodka/drink.hpp>
#include <boost/test/minimal.hpp>


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/oven/tests.hpp>
#include <pstade/oven/single_range.hpp>


#include <string>
#include <vector>
#include <pstade/oven/functions.hpp>


void test()
{
    namespace oven = pstade::oven;
    using namespace oven;

    std::string ans("a");

    {
        BOOST_CHECK( oven::equals(oven::make_single_range('a'), ans) );
    }
    {
        BOOST_CHECK( oven::equals('a'|as_single, ans) );
    }
    {
        char ch = 'a';
        BOOST_CHECK( oven::equals(oven::make_single_range(ch), ans) );
    }
}


int test_main(int, char*[])
{
    ::test();
    return 0;
}
