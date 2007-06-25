#include "./prefix.hpp"
#include <pstade/vodka/drink.hpp>
#include <boost/test/minimal.hpp>


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include "./detail/v1_tests.hpp"
#include <pstade/oven/sliced.hpp>


#include <iostream>
#include <string>
#include <boost/foreach.hpp>
#include <boost/mpl/assert.hpp>
#include <boost/type_traits/is_same.hpp>
#include <pstade/oven/counting.hpp>
#include "./detail/v1_core.hpp"
#include <pstade/oven/offset.hpp>
#include <pstade/oven/detail/before_stable_partition.hpp>


void test()
{
    namespace oven = pstade::oven;
    using namespace oven;

    {
        int rng[] = { 0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15 };
        int ans[] = { 2,6,10,14 };
        std::vector<char> expected = ans|copied;

        BOOST_CHECK( oven::test_RandomAccess_Readable_Writable(
            rng|sliced(2, 4) PSTADE_OVEN_BEFORE_STABLE_PARTITION,
            expected
        ) );
    }
    {
        int const ans[] = { 0,4,8,12 };
        BOOST_CHECK( oven::equals(ans,
            oven::counting(0, 16)|sliced(0, 4) PSTADE_OVEN_BEFORE_STABLE_PARTITION
        ) );

        BOOST_FOREACH (int x, oven::counting(0, 16)|sliced(0, 4)) {
            std::cout << x << std::endl;
        }
#if 0
        BOOST_CHECK( 4 ==
            (oven::counting(0, 16)|sliced(0, 4)).stride()
        );

        BOOST_CHECK( 0 ==
            (oven::counting(0, 16)|sliced(0, 4)).start()
        );
#endif
    }

    {
        int const ans[] = { 2,6,10,14 };
        BOOST_CHECK( oven::equals(ans,
            oven::counting(0, 16)|offset(2, 2)|sliced(0, 4)
        ) );
    }

    {
        int const answer[] = { 2,6,10,14 };
        BOOST_CHECK( oven::equals(answer,
            oven::counting(0, 16)|sliced(2, 4)
        ) );
    }

    {
        int const answer[] = { 2,6,10,14 };
        BOOST_CHECK( oven::equals(answer,
            oven::counting(0, 16)|sliced(2, 4)
        ) );
    }
}


int test_main(int, char*[])
{
    ::test();
    return 0;
}
