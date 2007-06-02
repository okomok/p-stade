#include <pstade/vodka/drink.hpp>
#define PSTADE_CONCEPT_CHECK


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/oven/memoized.hpp>


#include <string>
#include <iostream>
#include <sstream>
#include <pstade/oven/copy_range.hpp>
#include <pstade/oven/copied_to.hpp>
#include <pstade/oven/filtered.hpp>
#include <pstade/oven/stream_read.hpp>
#include <pstade/oven/io.hpp>
#include <pstade/oven/equals.hpp>
#include <pstade/oven/taken.hpp>
#include <pstade/oven/regular.hpp>
#include <iterator>
#include <boost/lambda/core.hpp>
#include <boost/lambda/lambda.hpp>
#include <iostream>


#include <pstade/unit_test.hpp>
#include "./int_tests.hpp"


void pstade_unit_test()
{
    namespace bll = boost::lambda;

    {
        std::string a("18284610528192");
        std::stringstream ss;
        ss << a;
        test::forward_constant(oven::stream_read<char>(ss)|memoized, a);
    }
    {
        int const src[] = { 1,2,5,3,6,8,6,1 };
        std::cout << (src|memoized);
    }
    {
        int a[] = { 5,1,3,5,1,3,1,3,1,6,78,14,1,3,6 };
        int b[] = { 5,1,3,5,1,3,1,3,1,6,78,14,1,3,6 };
        memo_table tb;
        PSTADE_fc(memoized(tb), a, b);
    }
    {
        std::string src("axaxaxbxbxbx");
        std::string s1; // snapshot
        std::string s2;
        std::string answer("bbb");

        BOOST_CHECK((
            equals(answer,
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
        PSTADE_ef(memoized);
    }
    {
        memo_table tb;
        PSTADE_ef(memoized(tb));
    }
    {
        std::string src("aaaaaaaaaaaaaaaa");
        test::emptiness(src|filtered(regular(bll::_1 == 'b'))|memoized);
    }
}
