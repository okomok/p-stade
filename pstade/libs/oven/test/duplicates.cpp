#include <pstade/vodka/drink.hpp>
#include <boost/test/minimal.hpp>


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/oven/tests.hpp>
#include <pstade/oven/duplicates.hpp>


//#include <iostream>
#include <string>
#include <pstade/oven/identities.hpp>


namespace oven = pstade::oven;
using namespace oven;


void test()
{
    //std::string src("11223444445");
    //std::cout << ::make_duplicates(src);

    {
        std::string ans("024679");
        std::vector<char> expected = ans|copied;

        BOOST_CHECK( oven::test_Forward_Readable(
            std::string("00122344444566778999")|duplicates,
            expected
        ) );

        BOOST_CHECK( oven::test_SinglePass_Readable(
            std::string("00122344444566778999")|identities(in_single_pass)|duplicates,
            expected
        ) );
    }
    {
        std::string ans("135678");
        std::vector<char> expected = ans|copied;

        BOOST_CHECK( oven::test_Forward_Readable(
            std::string("0112334555555667777888889")|duplicates,
            expected
        ) );

        BOOST_CHECK( oven::test_SinglePass_Readable(
            std::string("0112334555555667777888889")|identities(in_single_pass)|duplicates,
            expected
        ) );
    }
    {
        BOOST_CHECK( oven::test_empty(
            std::string("abcdefghij")|duplicates
        ) );
    }
    {
        BOOST_CHECK( oven::test_empty(
            std::string()|duplicates
        ) );
    }
}


int test_main(int, char*[])
{
    ::test();
    return 0;
}
