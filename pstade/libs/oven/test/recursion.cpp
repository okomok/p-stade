#include <pstade/vodka/drink.hpp>
#include <boost/test/minimal.hpp>


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/oven/tests.hpp>
#include <pstade/oven/recursion.hpp>


#include <pstade/oven/prepended.hpp>
#include <pstade/oven/any_range.hpp>
#include <pstade/oven/taken.hpp>


using namespace pstade::oven;


typedef
    any_range<int const&, boost::single_pass_traversal_tag>
range;


void test()
{
    range ones;

    int const one = 1;
    ones = recursion(ones)|prepended(one);

    int const ans[] = { 1,1,1,1,1,1,1,1 };
    BOOST_CHECK( equals(ans, ones|taken(8)) );
}


int test_main(int, char*[])
{
    ::test();
    return 0;
}