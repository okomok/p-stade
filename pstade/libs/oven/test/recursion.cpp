#include "./prefix.hpp"


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/oven/recursion.hpp>
#include <pstade/unit_test.hpp>
#include "./detail/test.hpp"


#include <pstade/oven/reversed.hpp>
#include <pstade/oven/single.hpp>
#include <pstade/oven/any_range.hpp>
#include <pstade/oven/taken.hpp>
#include <pstade/oven/copied.hpp>
#include <pstade/oven/shared.hpp>
#include <pstade/oven/jointed.hpp>
#include <pstade/oven/shared_single.hpp>
#include <pstade/oven/memoized.hpp>


#include <iostream>
#include <pstade/oven/with_data.hpp>
typedef boost::array<char, 5000> big_data;


namespace oven = pstade::oven;
using namespace oven;


typedef
    any_range<int const&, boost::forward_traversal_tag>
range;


range make_ones()
{
    range *pones = new range();

    *pones = shared_single(new int const(1))|jointed(recursion(*pones));

    return shared(pones);
}


void pstade_unit_test()
{
    { // reverse
        any_range<int const&, boost::bidirectional_traversal_tag> ones;

        int const one = 1;
        ones = recursion(ones)|jointed(single(one));

        int a[] = { 1,1,1,1,1,1,1,1 };
        test::forward_constant(ones|reversed|taken(8), a);
    }
    {
        ::range ones;

        int const one = 1;
        ones = single(one)|jointed(recursion(ones));

        int a[] = { 1,1,1,1,1,1,1,1 };
        test::forward_constant(ones|taken(8), a);
    }
    { // recursive memoized
        ::range ones;
        memo_table tb;

        int const one = 1;
        ones = single(one)|jointed(recursion(ones))|memoized(tb);

        int a[] = { 1,1,1,1,1,1,1,1 };
        test::forward_constant(ones|taken(8), a);
    }

    { // recursive memoized
        ::range x;
        memo_table tb;

        int const a1_7[] = { 1,2,3,4,5,6 };
        x = a1_7|jointed(recursion(x))|memoized(tb);

        int const a[] = { 1,2,3,4,5,6,1,2 };
        test::forward_constant(x|taken(8), a);
    }
    {
        int a[] = { 1,1,1,1,1,1,1,1 };
        test::forward_constant(::make_ones()|taken(8), a);
    }
}

