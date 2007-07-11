#include "./prefix.hpp"


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/oven/detail/foreach.hpp>
#include <pstade/minimal_test.hpp>


#include <string>


template<class Range>
void test_dependent(Range& rng)
{
    PSTADE_OVEN_FOREACH_TPL (reference r, rng)
        r = '2';

    PSTADE_OVEN_FOREACH_TPL (value_type v, rng) {
        BOOST_CHECK(v == '2');
    }
}


void pstade_minimal_test()
{
    {
        std::string str;
        PSTADE_OVEN_FOREACH (value_type v, str)
            BOOST_CHECK(false);
    }
    {
        std::string str("a");
        PSTADE_OVEN_FOREACH (reference r, str) {
            r = 'b';
        }

        BOOST_CHECK( str == "b" );
    }
    {
        std::string str("01234");
        int i = 0;
        PSTADE_OVEN_FOREACH (value_type r, str) {
            BOOST_CHECK(i == 0 ? r == '0' : true);
            BOOST_CHECK(i == 1 ? r == '1' : true);
            BOOST_CHECK(i == 2 ? r == '2' : true);
            BOOST_CHECK(i == 3 ? r == '3' : true);
            BOOST_CHECK(i == 4 ? r == '4' : true);
            ++i;
        }
        BOOST_CHECK(i == 5);
    }
    {
        std::string str("01234");
        int i = 0;
        PSTADE_OVEN_FOREACH (reference r, str) {
            BOOST_CHECK(i == 0 ? r == '0' : true);
            BOOST_CHECK(i == 1 ? r == '1' : true);
            BOOST_CHECK(i == 2 ? r == '2' : true);
            BOOST_CHECK(i == 3 ? r == '3' : true);
            BOOST_CHECK(i == 4 ? r == '4' : true);
            ++i;
        }
        BOOST_CHECK(i == 5);
    }
    {
        std::string str("abcdefg");
        ::test_dependent(str);
    }
}
