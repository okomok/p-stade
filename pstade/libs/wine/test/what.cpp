#include <pstade/vodka/drink.hpp>


// PStade.Wine
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/what.hpp>
#include <boost/test/minimal.hpp>


#include <pstade/oven/copied.hpp>
#include <string>
#include <vector>


using namespace pstade;


void test()
{
    std::vector<char> rng = std::string("hello")|oven::copied;
    BOOST_CHECK( what("tag", rng) == "<tag>hello</tag>" );
    BOOST_CHECK( what("tag", "hello") == "<tag>hello</tag>" );
    BOOST_CHECK( what("tag", 12) == "<tag>12</tag>" );
}


int test_main(int, char*[])
{
    ::test();
    return 0;
}
