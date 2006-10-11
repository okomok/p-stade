#include <pstade/vodka/drink.hpp>
#include <boost/test/minimal.hpp>


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/oven/tests.hpp>
#include <pstade/oven/slice_range.hpp>


#include <iostream>
#include <string>
#include <boost/foreach.hpp>
#include <boost/mpl/assert.hpp>
#include <boost/type_traits/is_same.hpp>
#include <pstade/oven/counting_range.hpp>
#include <pstade/oven/functions.hpp>
#include <pstade/oven/metafunctions.hpp>
#include <pstade/oven/memoize_range.hpp>
#include <pstade/oven/advance_range.hpp>


void test()
{
    namespace oven = pstade::oven;
    using namespace oven;

    {
        int rng[] = { 0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15 };
        int ans[] = { 2,6,10,14 };
        std::vector<char> expected = ans|copied;

        BOOST_CHECK( oven::test_RandomAccess_Readable_Writable(
            rng|sliced(2, 4),
            expected
        ) );
    }
    {
        int const ans[] = { 0,4,8,12 };
        BOOST_CHECK( oven::equals(ans,
            oven::from_0_to(16)|sliced(0, 4)
        ) );

        BOOST_FOREACH (int x, oven::from_0_to(16)|sliced(0, 4)) {
            std::cout << x << std::endl;
        }

        BOOST_CHECK( 4 ==
            (oven::from_0_to(16)|sliced(0, 4)).stride()
        );

        BOOST_CHECK( 0 ==
            (oven::from_0_to(16)|sliced(0, 4)).start()
        );
    }

    {
        int const ans[] = { 2,6,10,14 };
        BOOST_CHECK( oven::equals(ans,
            oven::from_0_to(16)|advanced(2)|sliced(0, 4)
        ) );
    }

    {
        int const answer[] = { 2,6,10,14 };
        BOOST_CHECK( oven::equals(answer,
            oven::make_counting_range(0, 16)|sliced(2, 4)
        ) );
    }

    {
        int const answer[] = { 2,6,10,14 };
        BOOST_CHECK( oven::equals(answer,
            oven::make_counting_range(0, 16)|sliced(2, 4)
        ) );
    }
}


typedef pstade::oven::slice_range<std::string> slice_rng_t;
BOOST_MPL_ASSERT((boost::is_same< pstade::oven::range_base<slice_rng_t>::type, std::string >));


int test_main(int, char*[])
{
    ::test();
    return 0;
}
