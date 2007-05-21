#include <pstade/unit_test.hpp>


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#define PSTADE_OVEN_TESTS_DONT_CALL_DISTANCE
#include <pstade/oven/tests.hpp>
#include <pstade/oven/recursion.hpp>


#include <pstade/oven/reversed.hpp>
#include <pstade/oven/single.hpp>
#include <pstade/oven/any_range.hpp>
#include <pstade/oven/taken.hpp>
#include <pstade/oven/copy_range.hpp>
#include <pstade/oven/shared.hpp>
#include <pstade/oven/jointed.hpp>
#include <pstade/oven/shared_single.hpp>
#include <pstade/oven/memoized.hpp>


namespace oven = pstade::oven;
using namespace pstade::oven;


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
    {
        range ones;

        int const one = 1;
        ones = single(one)|jointed(recursion(ones));

        int const ans_[] = { 1,1,1,1,1,1,1,1 };
        std::vector<int> ans = ans_|copied;
        BOOST_CHECK( oven::test_Forward_Readable(
            ones|taken(8),
            ans
        ) );
    }
    { // recursive memoized
        range ones;
        memo_table tb;

        int const one = 1;
        ones = single(one)|jointed(recursion(ones))|memoized(tb);

        int const ans_[] = { 1,1,1,1,1,1,1,1 };
        std::vector<int> ans = ans_|copied;
        BOOST_CHECK( oven::test_Forward_Readable(
            ones|taken(8),
            ans
        ) );
    }

    { // recursive memoized
        range x;
        memo_table tb;

        int const a1_7[] = { 1,2,3,4,5,6 };
        x = a1_7|jointed(recursion(x))|memoized(tb);

        int const ans_[] = { 1,2,3,4,5,6,1,2 };
        std::vector<int> ans = ans_|copied;
        BOOST_CHECK( oven::test_Forward_Readable(
            x|taken(8),
            ans
        ) );
    }
    { // reverse
        any_range<int const&, boost::bidirectional_traversal_tag> ones;

        int const one = 1;
        ones = recursion(ones)|jointed(single(one));

        int const ans_[] = { 1,1,1,1,1,1,1,1 };
        std::vector<int> ans = ans_|copied;
        BOOST_CHECK( oven::test_Forward_Readable(
            ones|reversed|taken(8),
            ans
        ) );
    }
    {
        int const ans_[] = { 1,1,1,1,1,1,1,1 };
        std::vector<int> ans = ans_|copied;
        BOOST_CHECK( oven::test_Forward_Readable(
            ::make_ones()|taken(8),
            ans
        ) );
    }
}

