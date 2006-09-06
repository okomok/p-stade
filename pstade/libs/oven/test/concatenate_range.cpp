#include <pstade/vodka/drink.hpp>
#include <boost/test/minimal.hpp>


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/oven/concatenate_range.hpp>


#include <vector>
#include <boost/range.hpp>
#include <string>
#include <pstade/oven/functions.hpp>
#include <pstade/oven/reverse_range.hpp>
#include <pstade/oven/tests.hpp>


void test()
{
    using namespace pstade;
    using namespace oven;

    std::vector<std::string> vec;
    vec.push_back("abcd");
    vec.push_back("efg");
    vec.push_back("h");
    vec.push_back("");
    vec.push_back("ij");
    vec.push_back("");
    vec.push_back("klmn");
    vec.push_back("");

    {
        BOOST_CHECK( oven::equals( vec|concatenated, std::string("abcdefghijklmn") ) );
    }

    {
        BOOST_CHECK( oven::equals( vec|concatenated|reversed, std::string("nmlkjihgfedcba") ) );
    }

    {
        BOOST_CHECK( oven::test_bidirectional(vec|concatenated) );
    }

    {
        std::vector<std::string> vec;
        vec.push_back("");
        vec.push_back("");
        vec.push_back("");
        BOOST_CHECK( boost::empty(vec|concatenated) );
        vec.push_back("ab");
        BOOST_CHECK( oven::equals(vec|concatenated, std::string("ab")) );
        vec.push_back("");
        vec.push_back("");
        BOOST_CHECK( oven::equals(vec|concatenated, std::string("ab")) );
    }   
}


int test_main(int, char*[])
{
    ::test();
    return 0;
}
