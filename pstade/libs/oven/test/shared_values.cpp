#include "./prelude.hpp"
#include <pstade/vodka/drink.hpp>
#include <boost/test/minimal.hpp>


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include "./detail/v1_tests.hpp"
#include <pstade/oven/shared_values.hpp>


#include <vector>
#include "./detail/v1_core.hpp"


namespace oven = pstade::oven;
using namespace oven;


boost::result_of<op_shared_values<>(int, int, int, int, int, int, int, int, int, int)>::type
make_values()
{
    return shared_values(0,1,2,3,4,5,6,7,8,9);
}


void test()
{
    {
        int ans[] = { 0,1,2,3,4,5,6,7,8,9 };
        std::vector<int> expected = ans|copied;

        BOOST_CHECK( oven::test_RandomAccess_Readable(
            ::make_values(),
            expected
        ) );
    }
    {
        // decay test
        shared_values("abc", "def", "ghi");
    }
}


int test_main(int, char*[])
{
    ::test();
    return 0;
}
