#include <pstade/vodka/drink.hpp>
#include <boost/test/minimal.hpp>


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/oven/map_value_range.hpp>


#include <iterator>
#include <string>
#include <map>
#include <boost/foreach.hpp>
#include <boost/range.hpp>
#include <pstade/oven/functions.hpp>


void test()
{
    namespace oven = pstade::oven;
    using namespace oven;

    std::map<int, std::string> vec;
    vec[3] = "hello";
    vec[4] = "value";


    BOOST_FOREACH( std::string& v, vec|map_values) {
        v = "a";
    }

    BOOST_CHECK( vec[3] == "a" && vec[4] == "a" );
    BOOST_CHECK( oven::distance(vec) == 2 );
}


int test_main(int, char*[])
{
    ::test();
    return 0;
}
