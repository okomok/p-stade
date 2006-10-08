#include <pstade/vodka/drink.hpp>
#include <boost/test/minimal.hpp>


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/oven/tests.hpp>
#include <pstade/oven/array_protect_range.hpp>


#include <string>
#include <pstade/oven/functions.hpp>


void test()
{
    namespace oven = pstade::oven;
    using namespace oven;

    std::vector<char> expected = std::string("hello, array_protect_range")|copied;
    expected.push_back('\0'); // contains null.

    {
        char str[] = "hello, array_protect_range";
        array_protect_range<char> src(str);
        BOOST_CHECK(oven::test_RandomAccess_Readable_Writable(src, expected));
    }
    {
        BOOST_CHECK(oven::test_RandomAccess_Readable("hello, array_protect_range"|array_protected, expected));
    }
}


int test_main(int, char*[])
{
    ::test();
    return 0;
}
