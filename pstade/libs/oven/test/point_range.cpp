#include <pstade/vodka/drink.hpp>
#include <boost/test/minimal.hpp>


// PStade.Oven
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/oven/point_range.hpp>


#include <cstring>
#include <string>
#include <vector>
#include <boost/range.hpp>
#include <pstade/oven/functions.hpp>
#include <pstade/oven/null_terminate_range.hpp>


void test()
{
    using namespace pstade;
    using namespace oven;

    {
        std::vector<int> vec;
        BOOST_CHECK(( boost::empty(vec|pointed) ));
    }
    {
        std::string const src("hello, point_range");
        std::vector<char> vec;
        vec.resize(oven::distance(src) + 1);
        std::strcpy(vec|pointed|begins, src.c_str());
        BOOST_CHECK(( oven::equals(vec|null_terminated, src) ));
    }
}


int test_main(int, char*[])
{
    ::test();
    return 0;
}
