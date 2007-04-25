#include <pstade/unit_test.hpp>


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#define PSTADE_OVEN_TESTS_DONT_CALL_DISTANCE
#include <pstade/oven/tests.hpp>
#include <pstade/oven/memoized.hpp>


#include <string>
#include <iostream>
#include <sstream>
#include <boost/range.hpp>
#include "./core.hpp"
#include <pstade/oven/copy_range.hpp>
#include <pstade/oven/copied_to.hpp>
#include <pstade/oven/filtered.hpp>
#include <pstade/oven/reading.hpp>
#include <pstade/oven/io.hpp>
#include <pstade/oven/taken.hpp>


#include <iterator>
#include <boost/lambda/core.hpp>
#include <boost/lambda/lambda.hpp>
#include <iostream>


void pstade_unit_test()
{
    namespace oven = pstade::oven;
    using namespace oven;
    namespace bll = boost::lambda;

    {
        std::string ans("18284610528192");
        std::stringstream ss;
        ss << ans;
        std::vector<char> expected = ans|copied;
        BOOST_CHECK( oven::test_Forward_Readable(
            oven::reading<char>(ss)|memoized,
            expected
        ) );
    }
    {
        int const src[] = { 1,2,5,3,6,8,6,1 };
        std::cout << (src|memoized);
    }

    {
        int const src[] = { 1,2,5,3,6,8,6,1 };
        memo_table tb;

        int const ans[] = { 1,2,5,3,6 };
        std::vector<int> expected = ans|copied;
        BOOST_CHECK( oven::test_Forward_Readable(
            src|memoized(tb)|taken(5),
            expected
        ) );
    }
    {
        std::string ans("18284610528192");
        memo_table tb;

        std::vector<char> expected = ans|copied;
        BOOST_CHECK( oven::test_Forward_Readable(
            ans|memoized(tb),
            expected
        ) );
    }
    {
        std::string src("axaxaxbxbxbx");
        std::string s1; // snapshot
        std::string s2;
        std::string answer("bbb");

        BOOST_CHECK((
            oven::equals(answer,
                src |
                    filtered(regular(bll::_1 != 'x')) |
                    memoized |
                    copied_to(std::back_inserter(s1)) |
                    filtered(regular(bll::_1 != 'a')) |
                    memoized |
                    copied_to(std::back_inserter(s2))
            )
        ));

        BOOST_CHECK( s1 == "aaabbb" );
        BOOST_CHECK( s2 == answer );
    }
    {
        BOOST_CHECK(( oven::test_empty(std::string()|memoized) ));
    }
    {
        memo_table tb;
        BOOST_CHECK(( oven::test_empty(std::string()|memoized(tb)) ));
    }
    {
        std::string src("aaaaaaaaaaaaaaaa");
        BOOST_CHECK(( oven::test_empty(src|filtered(regular(bll::_1 == 'b'))|memoized) ));
    }
}

