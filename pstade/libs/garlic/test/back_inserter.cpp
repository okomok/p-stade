#include <pstade/vodka/drink.hpp>
#include <boost/test/minimal.hpp>


// PStade.Wine
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/garlic/back_inserter.hpp>


#include <vector>
#include <string>
#include <sstream>
#include <pstade/oven/functions.hpp>


void test()
{
    using namespace pstade;

    std::string src("abcdefg");
    
    {
        std::string dst;
        oven::copy(src, garlic::back_inserter(dst));
        BOOST_CHECK(oven::equals(src, dst));
    }

    {
        std::vector<char> dst;
        oven::copy(src, garlic::back_inserter(dst));
        BOOST_CHECK(oven::equals(src, dst));
    }

    {
        std::stringstream dst;
        oven::copy(src, garlic::back_inserter(dst));
        BOOST_CHECK(oven::equals(src, dst.str()));
    }
}


int test_main(int, char*[])
{
    ::test();
    return 0;
}
