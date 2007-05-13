#include <pstade/vodka/drink.hpp>
#include <boost/test/minimal.hpp>


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/oven/locale.hpp>


#include <string>
#include <pstade/oven/functions.hpp>
#include <pstade/oven/filter_range.hpp>
#include <pstade/oven/transform_range.hpp>


void test()
{
    using namespace pstade;
    using namespace oven;

    {
        BOOST_CHECK( oven::equals(
            std::string("ABCDE"),
            std::string("abCde")|transformed(to_upper)
        ));
    }
    {
        BOOST_CHECK( oven::equals(
            std::string("abcde"),
            std::string("AbCdE")|transformed(to_lower)
        ));
    }

    {
        BOOST_CHECK( oven::equals(
            std::string("abcde"),
            std::string("a1b23c4d5e")|filtered(is_alpha)
        ));
    }
    {
        BOOST_CHECK( oven::equals(
            std::string("12345"),
            std::string("a1b23c4d5e")|filtered(is_digit)
        ));
    }
}


int test_main(int, char*[])
{
    ::test();
    return 0;
}
