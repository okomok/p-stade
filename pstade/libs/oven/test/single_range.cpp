#include <pstade/vodka/drink.hpp>
#include <boost/test/minimal.hpp>


// PStade.Oven
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/oven/single_range.hpp>


#include <string>
#include <vector>
#include <pstade/oven/functions.hpp>


void test()
{
    using namespace pstade;
    namespace _ = oven;

    std::string ans("a");

    {
        BOOST_CHECK( _::equals(_::make_single_range('a'), ans) );
    }

    {
        char ch = 'a';
        BOOST_CHECK( _::equals(_::make_single_range(ch), ans) );
    }
}


int test_main(int, char*[])
{
    ::test();
    return 0;
}
