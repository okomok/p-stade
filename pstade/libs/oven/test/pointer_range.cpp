#include <pstade/vodka/drink.hpp>
#include <boost/test/minimal.hpp>


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/oven/pointer_range.hpp>


#include <cstring>
#include <string>
#include <vector>
#include <boost/range.hpp>
#include <pstade/functional.hpp>
#include <pstade/oven/functions.hpp>
#include <pstade/oven/take_while_range.hpp>


void test()
{
    namespace oven = pstade::oven;
    using namespace oven;

    {
        std::vector<int> vec;
        BOOST_CHECK(( boost::empty(vec|pointers) ));
    }
    {
        std::string const src("hello, pointer_range");
        std::vector<char> vec;
        vec.resize(oven::distance(src) + 1);
        std::strcpy(vec|pointers|begins, src.c_str());
        BOOST_CHECK(( oven::equals(vec|taken_while(pstade::not_(pstade::is_zero)), src) ));
    }
}


int test_main(int, char*[])
{
    ::test();
    return 0;
}
