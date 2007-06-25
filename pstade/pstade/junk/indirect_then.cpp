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
#include <pstade/oven/indirect_then.hpp>


#include <functional>


void test()
{
    namespace oven = pstade::oven;
    using namespace oven;

    {
        int i1 = -1;
        BOOST_CHECK( 1 == indirect_then(std::negate<int>())(&i1) );
    }
    {
        int i1 = 10;
        int i2 = 12;
        BOOST_CHECK( indirect_then(std::less<int>())(&i1, &i2) );
    }
}


int test_main(int, char*[])
{
    ::test();
    return 0;
}
