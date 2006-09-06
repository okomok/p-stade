#include <pstade/vodka/drink.hpp>
#include <boost/test/minimal.hpp>


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/oven/array_range.hpp>


#include <string>
#include <boost/range.hpp>
#include <pstade/oven/functions.hpp>
#include <pstade/oven/copy_range.hpp>


void test()
{
    using namespace pstade;
    using namespace oven;

    {
        std::string str("hello, array_range");
        array_range<char> arr(oven::distance(str));
        str|copied_to(arr);
        BOOST_CHECK(oven::equals(str, arr));
    }
}


int test_main(int, char*[])
{
    ::test();
    return 0;
}
