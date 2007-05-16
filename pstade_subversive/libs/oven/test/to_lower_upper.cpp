#include <pstade/vodka/drink.hpp>
#include <boost/test/minimal.hpp>


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/oven/tests.hpp>
#include <pstade/oven/to_lower.hpp>
#include <pstade/oven/to_upper.hpp>


#include <string>
#include "./core.hpp"
#include <pstade/oven/tests.hpp>


void test()
{
    namespace oven = pstade::oven;
    using namespace oven;

    {
        BOOST_CHECK( equals(
            std::string("AbCdEFG")|to_lower,
            std::string("abcdefg")
        ) );
    }
    {
        BOOST_CHECK( equals(
            std::string("AbCdEFG")|to_lower(std::locale()),
            std::string("abcdefg")
        ) );
    }
    {
        BOOST_CHECK( equals(
            std::string("AbCdEFG")|to_upper,
            std::string("ABCDEFG")
        ) );
    }
    {
        BOOST_CHECK( equals(
            std::string("AbCdEFG")|to_upper(std::locale()),
            std::string("ABCDEFG")
        ) );
    }
}


int test_main(int, char*[])
{
    ::test();
    return 0;
}
