#include <pstade/vodka/drink.hpp>
#include <boost/test/minimal.hpp>


// PStade.Oven
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/oven/sequence_cast.hpp>


#include <string>
#include <vector>
#include <pstade/oven/equal.hpp>


void test()
{
    using namespace pstade;
    using namespace oven;

    {
        std::string str("abcdefg");
        std::vector<char> vec = oven::sequence_cast< std::vector<char> >(str);
        BOOST_CHECK( oven::equals(vec, str) );
    }

    {
        std::string str("abcdefg");
        std::vector<char> vec = oven::sequence(str);
        BOOST_CHECK( oven::equals(vec, str) );
    }
}


int test_main(int, char*[])
{
    ::test();
    return 0;
}
