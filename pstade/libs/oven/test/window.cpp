#include "./prefix.hpp"
#include <pstade/vodka/drink.hpp>


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/oven/window.hpp>
#include <boost/test/minimal.hpp>
#include "./detail/v1_tests.hpp"


#include <string>
#include <vector>
#include "./detail/v1_core.hpp"


void test()
{
    namespace oven = pstade::oven;
    using namespace oven;

    {
        int A[] = { 0,1,2,3,4,5,6,7,8,9 };
        int ans[] = { 3,4,5,6,7 };
        std::vector<int> expected = ans|copied;

        BOOST_CHECK( oven::test_RandomAccess_Readable_Writable(
            A|window(3, 8),
            expected
        ) );
    }

    {
        int A[] = { 0,1,2,3,4,5,6,7,8,9 };
        std::vector<int> expected = A|copied;

        BOOST_CHECK( oven::test_RandomAccess_Readable_Writable(
            A|window(3, 8)|window(-3, 5+2),
            expected
        ) );
    }
    std::string src("0123456");
    {
        BOOST_CHECK( oven::equals(oven::make_window(src, 0, 0), std::string("")) );
    }

    {
        BOOST_CHECK( oven::equals(src|window(1, 6), std::string("12345")) );
    }
}


int test_main(int, char*[])
{
    ::test();
    return 0;
}
