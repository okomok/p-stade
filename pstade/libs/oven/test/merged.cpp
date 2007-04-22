#include <pstade/vodka/drink.hpp>
#include <boost/test/minimal.hpp>


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/oven/tests.hpp>
#include <pstade/oven/merged.hpp>


#include <cctype>
#include <iostream>
#include <string>
#include "./core.hpp"
#include <pstade/oven/algorithm.hpp>
#include <pstade/oven/tests.hpp>
#include <pstade/oven/to_stream.hpp>
#include <pstade/oven/as_c_str.hpp>
#include <pstade/test.hpp>


namespace oven = pstade::oven;
using namespace oven;


bool lt_nocase(char c1, char c2)
{
    return std::tolower(c1) < std::tolower(c2);
}


template<class Range1, class Range2>
typename boost::result_of<op_make_merged<>(Range1&, Range2&)>::type
make_merge_range_(Range1& rng1, Range2& rng2)
{
    return oven::make_merged(rng1, rng2);
}


void test()
{
    {
        int A1[] = {1,6,7,10,14,17};
        int A2[] = {2,5,8,11,13,18};
        int A3[] = {3,4,9,12,15,16};
        int AA[] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18};
        std::vector<int> expected = AA|copied;

        BOOST_CHECK( oven::test_Forward_Readable(
            A1|merged(A2)|merged(A3),
            expected
        ) );
    }
    {
        std::string A1("abbbfH");
        std::string A2("ABbCDFFhh");
        std::string AA("aAbbbBbCDfFFHhh");
        std::vector<char> expected = AA|copied;

        BOOST_CHECK( oven::test_Forward_Readable(
            A1|merged(A2, &::lt_nocase),
            expected
        ) );
    }
    {
        int A1[] = {1,3,5,7,9,11};
        int A2[] = {1,1,2,3,5,8,13};
        int AA[] = {1,1,1,2,3,3,5,5,7,8,9,11,13};

        BOOST_CHECK( oven::equals(A1|merged(A2), AA) );
        oven::copy(A1|merged(A2), to_stream(std::cout));
    }
    {
        std::string A1("abbbfH");
        std::string A2("ABbCDFFhh");
        std::string AA("aAbbbBbCDfFFHhh");
        BOOST_CHECK( oven::equals(A1|merged(A2, &::lt_nocase), AA) );
        oven::copy(A1|merged(A2, &::lt_nocase), to_stream(std::cout));
        // std::cout << std::endl;
        // oven::merge(A1, A2, to_stream(std::cout), &lt_nocase); 
    }
}


int test_main(int, char*[])
{
    ::test();
    return 0;
}
