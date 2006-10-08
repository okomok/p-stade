#include <pstade/vodka/drink.hpp>
#include <boost/test/minimal.hpp>


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/oven/tests.hpp>
#include <pstade/oven/array_range.hpp>


#include <string>
#include <vector>
#include <pstade/oven/functions.hpp>


void test()
{
    namespace oven = pstade::oven;
    using namespace oven;

    {
        std::vector<char> expected = std::string("hello, array_range")|copied;
        array_range<char> rng(oven::distance(expected));
        oven::copy(expected, rng|begins);

        BOOST_CHECK(oven::test_RandomAccess_Readable_Writable(rng, expected));
    }
}


int test_main(int, char*[])
{
    ::test();
    return 0;
}
