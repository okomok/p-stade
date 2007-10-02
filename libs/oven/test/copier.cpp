#include "./prefix.hpp"


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/oven/copier.hpp>
#include <pstade/minimal_test.hpp>


#include <pstade/oven/algorithm.hpp>
#include <iterator>
#include <pstade/oven/equals.hpp>
#include <vector>


void pstade_minimal_test()
{
    namespace oven = pstade::oven;
    using namespace oven;

    {
        std::vector<int> v1;
        std::vector<int> v2;
        std::vector<int> v3;
        int b[] = {1,3,4,5,3,2,5,1,2};

        copy(b,
            copier(std::back_inserter(v1)) |= copier(std::back_inserter(v2))
            |= std::back_inserter(v3) );

        BOOST_CHECK( equals(v1, b) );
        BOOST_CHECK( equals(v2, b) );
        BOOST_CHECK( equals(v3, b) );
    }
}
