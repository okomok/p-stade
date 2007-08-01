#include <pstade/vodka/drink.hpp>


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/oven/parallel_equals.hpp>
#include <pstade/oven/parallel_for_each.hpp>
#include <pstade/unit_test.hpp>


using namespace pstade::oven;


void change_array_body(int& x)
{
    x *= 2;
}


void pstade_unit_test()
{
    int b[] = { 5, 2, 3, 3, 1, 7, 3, 2, 8, 9, 2 };
    parallel_for_each(2, b, &::change_array_body);

    int a[] = {10, 4, 6, 6, 2,14, 6, 4,16,18, 4 };
    BOOST_CHECK( parallel_equals(2, a, b) );
}
