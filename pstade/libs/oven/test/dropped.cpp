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
#include <pstade/oven/identities.hpp>


void test()
{
    namespace oven = pstade::oven;
    using namespace oven;

    {
        std::string rng("hello, drop_range!");
        std::vector<char> expected = std::string("range!")|copied;

        BOOST_CHECK( oven::test_RandomAccess_Readable_Writable(
            rng|dropped(7)|dropped(5), expected
        ) );

        BOOST_CHECK( oven::test_empty(
            rng|dropped(7)|dropped(500)
        ) );

        BOOST_CHECK( oven::test_empty(
            rng|dropped(distance(rng))
        ) );
    }
    {
        std::string src("hello, drop_range!");
        BOOST_CHECK( oven::equals(src|dropped(7)|dropped(5), std::string("range!")) );
        BOOST_CHECK( oven::equals(src|dropped(7000), std::string()) );
    }
    {
        std::string src("hello, drop_range!");
        BOOST_CHECK( oven::equals(src|identities(single_pass_tag)|dropped(7)|dropped(5), std::string("range!")) );
        BOOST_CHECK( oven::equals(src|identities(single_pass_tag)|dropped(7000), std::string()) );
        BOOST_CHECK( oven::equals(src|identities(single_pass_tag)|dropped(distance(src)), std::string()) );
    }
}


int test_main(int, char*[])
{
    ::test();
    return 0;
}
