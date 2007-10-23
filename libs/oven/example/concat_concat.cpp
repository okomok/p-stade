#include <pstade/vodka/drink.hpp>


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <vector>
#include <pstade/oven/concatenated.hpp>
#include <pstade/oven/equals.hpp>
#include <pstade/unit_test.hpp>
#include "../test/detail/test.hpp"


namespace oven = pstade::oven;
using namespace oven;


void pstade_unit_test()
{
    {
        typedef std::vector<int> v0_t;
        typedef std::vector<v0_t> v1_t;
        typedef std::vector<v1_t> v2_t;

        v0_t v0_0;
        v0_0.push_back(0);
        v0_0.push_back(1);

        v0_t v0_1;
        v0_1.push_back(2);
        v0_1.push_back(3);
        v0_1.push_back(4);

        v0_t v0_2;
        v0_2.push_back(5);
        v0_2.push_back(6);
        v0_2.push_back(7);
        v0_2.push_back(8);

        v1_t v1_0;
        v1_0.push_back(v0_0);
        v1_0.push_back(v0_1);

        v1_t v1_1;
        v1_1.push_back(v0_0);
        v1_1.push_back(v0_2);

        v2_t v2;
        v2.push_back(v1_0);
        v2.push_back(v1_1);

        int const answer[] = { 0,1,2,3,4,0,1,5,6,7,8 };
        test::bidirectional_swappable(v2|concatenated|concatenated, answer);
    }
}
