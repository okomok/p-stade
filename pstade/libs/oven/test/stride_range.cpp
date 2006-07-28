#include <pstade/vodka/drink.hpp>
#include <boost/test/minimal.hpp>


// PStade.Oven
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/oven/stride_range.hpp>


#include <iostream>
#include <boost/foreach.hpp>
#include <pstade/oven/counting_range.hpp>
#include <pstade/oven/functions.hpp>
#include <pstade/oven/shift_range.hpp>


void test()
{
    using namespace pstade;
    using namespace oven;

    {
        int const ans[] = { 0,4,8,12 };
        BOOST_CHECK( oven::equals(ans,
            oven::zero_to(16)|stridden(4)
        ) );

        BOOST_FOREACH (int x, oven::zero_to(16)|stridden(4)) {
            std::cout << x << std::endl;
        }

        BOOST_CHECK( 4 ==
            (oven::zero_to(16)|stridden(4)).length()
        );
    }

    {
        int const ans[] = { 2,6,10,14 };
        BOOST_CHECK( oven::equals(ans,
            oven::zero_to(16)|shifted(2)|stridden(4)
        ) );
    }

    {
        int const answer[] = { 2,6,10,14 };
        BOOST_CHECK( oven::equals(answer,
            oven::make_counting_range(0, 16)|stridden(4, 2)
        ) );
    }
}


int test_main(int, char*[])
{
    ::test();
    return 0;
}
