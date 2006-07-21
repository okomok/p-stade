#include <pstade/vodka/drink.hpp>
#include <boost/test/minimal.hpp>


// PStade.Oven
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/oven/append_range.hpp>


#include <string>
#include <vector>
#include <pstade/oven/functions.hpp>
#include <pstade/oven/single_range.hpp>


void test()
{
    using namespace pstade;
    using namespace oven;
    namespace _ = oven;

    const std::string src("abcd");
    std::string ans("abcde");

    {
        std::string src("abcd");
        char ch = 'e';
        append_range<std::string, char> rng(src, ch);
        BOOST_CHECK( _::equals(rng, ans) );
    }

    {
        std::string src("abcd"); // mutable
        char ch = 'e'; // mutable
        BOOST_CHECK( _::equals(_::make_append_range(src, ch), ans) );
    }

    {
        BOOST_CHECK( _::equals(src|appended('e'), ans) );

        std::cout << std::endl;
        char ch = 'e';
        BOOST_FOREACH(char c, src|appended(ch)) {
            std::cout << c;
        }
        std::cout << std::endl;
    }

    {
        BOOST_CHECK( _::equals(
            std::string("ab")|
                appended('c')|appended('d')|appended('e'),
            ans)
        );
    }
}


int test_main(int, char*[])
{
    ::test();
    return 0;
}
