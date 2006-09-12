#include <pstade/vodka/drink.hpp>
#include <boost/test/minimal.hpp>


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/oven/to_counter.hpp>


#include <boost/range.hpp>
#include <pstade/oven/functions.hpp>


using namespace pstade;
using namespace oven;


void test()
{
    {
        int const rng[] = { 0,0,1,1,2,3,3,3,4,4,4,4,4,5,5 };
        int i = oven::unique_copy(rng, oven::to_counter(0))|to_counter_base;
        int j = oven::counter_base(oven::unique_copy(rng, oven::to_counter(0)));
        BOOST_CHECK( i == j && j == 6 );
        BOOST_CHECK( 7 == (oven::unique_copy(rng, oven::to_counter(1))|to_counter_base) );
    }
}


int test_main(int, char*[])
{
    ::test();
    return 0;
}
