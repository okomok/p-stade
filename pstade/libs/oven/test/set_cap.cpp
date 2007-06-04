#include <pstade/vodka/drink.hpp>
#include <boost/test/minimal.hpp>


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include "./detail/v1_tests.hpp"
#include <pstade/oven/set_cap.hpp>


#include <cctype> // tolower
#include <iostream>
#include <string>
#include "./detail/v1_core.hpp"
#include "./detail/v1_tests.hpp"
#include <pstade/oven/stream_writer.hpp>
#include <pstade/oven/as_c_str.hpp>


bool lt_nocase(char c1, char c2)
{
    return std::tolower(c1) < std::tolower(c2);
}


void test()
{
    namespace oven = pstade::oven;
    using namespace oven;

    {
        int A1[] = {1,3,5,7,9,11};
        int A2[] = {1,1,2,3,5,8,13};
        int AA[] = {1,3,5};
        std::vector<int> expected = AA|copied;

        BOOST_CHECK( oven::test_Forward_Readable(
            A1|set_cap(A2),
            expected
        ) );
    }
    {
        std::string A1("abbBBfhH");
        std::string A2("ABBCDFFH");
        std::string AA("abbfh");
        std::vector<char> expected = AA|copied;

        BOOST_CHECK( oven::test_Forward_Readable(
            A1|set_cap(A2, &::lt_nocase),
            expected
        ) );
    }
    {
        BOOST_CHECK( oven::test_empty(
            std::string()|set_cap( std::string() )
        ) );
    }
    {
        BOOST_CHECK( oven::test_empty(
            std::string("acefhikm")|set_cap( std::string("bdgjlnop") )
        ) );
    }
}


int test_main(int, char*[])
{
    ::test();
    return 0;
}
