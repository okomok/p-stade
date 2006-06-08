#include <pstade/vodka/drink.hpp>
#include <boost/test/minimal.hpp>


// PStade.Oven
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/oven/prepend_range.hpp>


#include <string>
#include <vector>
#include <pstade/oven/equal.hpp>
#include <pstade/oven/single_range.hpp>


void test()
{
    using namespace pstade;
    using namespace oven;
    namespace _ = oven;

    const std::string src("bcde");
    std::string ans("abcde");

    {
        std::string src("bcde"); // mutable
        char ch = 'a'; // mutable
        BOOST_CHECK( _::equals(_::make_prepend_range(src, ch), ans) );
    }

    {
        BOOST_CHECK( _::equals(src|prepended('a'), ans) );

        std::cout << std::endl;
        const char ch = 'a';
        BOOST_FOREACH(char c, src|prepended(ch)) {
            std::cout << c;
        }
        std::cout << std::endl;
    }

    {
        BOOST_CHECK( _::equals(
            std::string("de")|
                prepended('c')|prepended('b')|prepended('a'),
            ans)
        );
    }
}


int test_main(int, char*[])
{
    ::test();
    return 0;
}
