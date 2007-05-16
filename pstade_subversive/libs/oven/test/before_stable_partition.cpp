#include <pstade/vodka/drink.hpp>
#include <boost/test/minimal.hpp>


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/oven/tests.hpp>
#include <pstade/oven/before_stable_partition.hpp>


#include <vector>
#include <pstade/oven/copy_range.hpp>
#include <pstade/oven/counting.hpp>
#include <pstade/oven/permuted.hpp>


void test()
{
    namespace oven = pstade::oven;
    using namespace oven;

    {
        int elements[] = { 0,1,2,3,4,5,6 };
        std::vector<int> expected = elements|copied;

        BOOST_CHECK( oven::test_RandomAccess_Readable_Writable(
            elements|permuted(counting(0, 7)) PSTADE_OVEN_BEFORE_STABLE_PARTITION,
            expected
        ) );
    }    
}


int test_main(int, char*[])
{
    ::test();
    return 0;
}
