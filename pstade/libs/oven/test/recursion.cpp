#include <pstade/unit_test.hpp>


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/oven/tests.hpp>
#include <pstade/oven/recursion.hpp>


#include <pstade/oven/reversed.hpp>
#include <pstade/oven/appended.hpp>
#include <pstade/oven/prepended.hpp>
#include <pstade/oven/any_range.hpp>
#include <pstade/oven/taken.hpp>
#include <pstade/oven/copy_range.hpp>
#include <pstade/oven/shared.hpp>
#include <pstade/oven/jointed.hpp>
#include <pstade/oven/as_single.hpp>
#include <pstade/oven/memoized.hpp>


namespace oven = pstade::oven;
using namespace pstade::oven;


typedef
    any_range<int const&, boost::forward_traversal_tag>
range;


range make_ones()
{
    range *pones = new range();

    *pones = new int const(1)|as_shared_single|jointed(recursion(*pones));

    return pones|shared;
}


void pstade_unit_test()
{
    {
        range ones;

        int const one = 1;
        ones = recursion(ones)|prepended(one);

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
        ones = recursion(ones)|prepended(one)|memoized(tb);

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
        ones = recursion(ones)|appended(one);

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

