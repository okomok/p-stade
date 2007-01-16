#include <pstade/vodka/drink.hpp>
#include <boost/test/minimal.hpp>


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/oven/tests.hpp>
#include <pstade/oven/dropped.hpp>


#include <string>
#include <vector>
#include <boost/range.hpp>
#include <pstade/oven/functions.hpp>


void test()
{
    namespace oven = pstade::oven;
    using namespace oven;

    {
        std::string rng("hello, drop_range!");
        std::vector<char> expected = std::string("range!")|copied;
        BOOST_CHECK( oven::test_RandomAccess_Readable_Writable(rng|dropped(7)|dropped(5), expected) );
    }
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
