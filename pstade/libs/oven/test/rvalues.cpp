#include <pstade/vodka/drink.hpp>
#include <boost/test/minimal.hpp>


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/oven/tests.hpp>
#include <pstade/oven/rvalues.hpp>
#include <pstade/oven/counting.hpp>
#include <pstade/oven/front_back.hpp>
#include "./core.hpp"



void test()
{
    namespace oven = pstade::oven;
    using namespace oven;

    {
        BOOST_CHECK( back(counting(0, 5)|rvalues) == 4 );
    }
}


int test_main(int, char*[])
{
    ::test();
    return 0;
}
