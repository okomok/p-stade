#include <pstade/vodka/drink.hpp>
#include <boost/test/minimal.hpp>


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/oven/tests.hpp>
#include <pstade/oven/cleared.hpp>


#include <string>
#include "./core.hpp"


void test()
{
    namespace oven = pstade::oven;
    using namespace oven;

    {
        std::string str("hello, clear_range!");
        BOOST_CHECK( oven::test_empty(str|cleared) );
    }
}


int test_main(int, char*[])
{
    ::test();
    return 0;
}
