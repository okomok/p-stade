#include "./prefix.hpp"
#include <pstade/vodka/drink.hpp>


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/oven/map_keys.hpp>
#include <boost/test/minimal.hpp>
#include "./detail/v1_tests.hpp"


#include <iterator>
#include <string>
#include <map>
#include <boost/foreach.hpp>
#include <boost/range.hpp>
#include "./detail/v1_core.hpp"


void test()
{
    namespace oven = pstade::oven;
    using namespace oven;

    std::map<int, std::string> vec;
    vec[3] = "hello";
    vec[4] = "key";

    BOOST_FOREACH (int i, vec|map_keys) {
        std::cout << i;
    }
}


int test_main(int, char*[])
{
    ::test();
    return 0;
}
