#include <pstade/vodka/drink.hpp>
#include <boost/test/minimal.hpp>


// PStade.Wine
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/locale.hpp>


#include <string>
#include <pstade/oven/equals.hpp>
#include <pstade/oven/filtered.hpp>
#include <pstade/oven/transformed.hpp>


void test()
{
    using namespace pstade;

    {
        BOOST_CHECK(to_upper('a') == 'A');
        BOOST_CHECK(to_lower('A') == 'a');
    }
    {
        BOOST_CHECK( oven::equals(
            std::string("ABCDE"),
            std::string("abCde")|oven::transformed(to_upper)
        ));
    }
    {
        BOOST_CHECK( oven::equals(
            std::string("abcde"),
            std::string("AbCdE")|oven::transformed(to_lower)
        ));
    }
    {
        BOOST_CHECK( oven::equals(
            std::string("abcde"),
            std::string("AbCdE")
                |oven::transformed(to_lower)|oven::transformed(to_upper)|oven::transformed(to_lower)
        ));
    }

    {
        BOOST_CHECK( oven::equals(
            std::string("abcde"),
            std::string("a1b23c4d5e")|oven::filtered(is_alpha)
        ));
    }
    {
        BOOST_CHECK( oven::equals(
            std::string("12345"),
            std::string("a1b23c4d5e")|oven::filtered(is_digit)
        ));
    }
    {
        BOOST_CHECK( iequal_to('a', 'A') );
        BOOST_CHECK( iequal_to('a', 'A', std::locale()) );
    }
}


int test_main(int, char*[])
{
    ::test();
    return 0;
}
