#include <pstade/vodka/drink.hpp>
#include <boost/test/minimal.hpp>


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/oven/tests.hpp>
#include <pstade/oven/empty_range.hpp>


#include <boost/range/empty.hpp>
#include "./core.hpp"


void test()
{
    namespace oven = pstade::oven;
    using namespace oven;

    {
        empty_range<int> rng;
        BOOST_CHECK( oven::test_empty(rng) );
    }
    {
        BOOST_CHECK( boost::empty( empty_range<int>() ) );
        BOOST_CHECK( oven::equals( empty_range<char>(), empty_range<char>() ) );
    }
}


int test_main(int, char*[])
{
    ::test();
    return 0;
}
