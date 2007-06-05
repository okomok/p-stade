#include "./prelude.hpp"
#include <pstade/vodka/drink.hpp>
#include <boost/test/minimal.hpp>


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include "./detail/v1_tests.hpp"
#include <pstade/oven/iteration.hpp>


#include <iostream>
#include <boost/foreach.hpp>
#include "./detail/v1_core.hpp"
#include <pstade/oven/taken.hpp>
#include <pstade/oven/taken_while.hpp>
#include <pstade/oven/algorithm.hpp>

#include <boost/lambda/lambda.hpp>
#include <boost/lambda/core.hpp>


int increment(int x)
{
    return x + 1;
}

bool not_10(int x)
{
    return x != 10;
}


void test()
{
    namespace oven = pstade::oven;
    using namespace oven;

    {
        int ans[]  = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, };
        std::vector<int> expected = ans|copied;

        BOOST_CHECK( oven::test_Forward_Readable(
            iteration(0, &increment)|taken(10),
            expected
        ) );
    }

    {
        int ans[]  = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, };

        BOOST_CHECK( oven::equal( // not 'equal*s*'
            ans, iteration(0, &increment)|begin
        ) );

        BOOST_CHECK( oven::equals(
            ans, iteration(0, &increment)|taken_while(&not_10)
        ) );

        BOOST_CHECK( oven::equals(
            ans, iteration(0, &increment)|taken(10)
        ) );

        BOOST_FOREACH (int i , iteration(0, &increment)|taken(10)) {
            std::cout << i << ",";
        }
    }

    {
        namespace lambda = boost::lambda;
        int answer[] = { 1,2,4,8,16 };
        BOOST_CHECK( oven::equals(answer,
            oven::iteration(1, regular(lambda::_1 * 2))|oven::taken(5)
        ) );
    }
}


int test_main(int, char*[])
{
    ::test();
    return 0;
}
