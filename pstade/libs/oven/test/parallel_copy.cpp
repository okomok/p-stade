#include "./prefix.hpp"

// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/oven/parallel_copy.hpp>
#include <pstade/unit_test.hpp>


#include <pstade/oven/equals.hpp>


void pstade_unit_test()
{
    namespace oven = pstade::oven;
    using namespace oven;

    {
        int a[21] = { 1,2,13,6,1,3,4,16,3,1,7,4,2,1,7,4,2,1,3,5,1 };
        int b[21];
        parallel_copy(5, a, &b[0]);

        BOOST_CHECK( equals(a, b) );
    }
}
