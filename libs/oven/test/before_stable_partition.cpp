#include "./prefix.hpp"
#include <pstade/vodka/drink.hpp>
#define PSTADE_CONCEPT_CHECK


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/oven/detail/before_stable_partition.hpp>
#include <pstade/minimal_test.hpp>
#include "./detail/test.hpp"


#include <vector>
#include <pstade/oven/copied.hpp>
#include <pstade/oven/counting.hpp>
#include <pstade/oven/permuted.hpp>


void pstade_minimal_test()
{
    namespace oven = pstade::oven;
    using namespace oven;

    {
        int elements[] = { 0,1,2,3,4,5,6 };
        std::vector<int> a = elements|copied;

        test::random_access_swappable(
            elements|permuted(counting(0, 7)) PSTADE_OVEN_BEFORE_STABLE_PARTITION,
            a
        );
    }    
}
