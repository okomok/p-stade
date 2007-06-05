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
#include <pstade/oven/scanned.hpp>


#include <numeric>
#include <iostream>
#include <iterator>
#include <string>
#include <vector>
#include <boost/foreach.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/range.hpp>
#include "./detail/v1_core.hpp"
#include <pstade/oven/regular.hpp>
#include <boost/lambda/core.hpp>
#include <boost/lambda/lambda.hpp>
#include <pstade/oven/dropped.hpp>
#include <pstade/functional.hpp> // plus


int minus(int state, int x)
{
    return state - x;
}


std::string stringize(std::string const& state, int i)
{
    return state + boost::lexical_cast<std::string>(i);
}


void test()
{
    namespace oven = pstade::oven;
    using namespace oven;

    {
        int rng[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9,10};
        int ans[] = { 0, 1, 3, 6,10,15,21,28,36,45,55};
        std::vector<int> expected = ans|copied;

        BOOST_CHECK( oven::test_Forward_Readable(
            rng|scanned(0, pstade::plus),
            expected
        ) );

        namespace lambda = boost::lambda;
        BOOST_CHECK( oven::test_Forward_Readable(
            rng|scanned(0, regular(lambda::_1 + lambda::_2)),
            expected
        ) );
    }
    {
        int rng[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9,10};
        int ans[] = { 1, 3, 6,10,15,21,28,36,45,55};
        std::vector<int> expected = ans|copied;

        BOOST_CHECK( oven::test_Forward_Readable(
            rng|scanned(pstade::plus),
            expected
        ) );
    }
    {
        int rng[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9,10};
        std::vector<int> ans;
        std::partial_sum(boost::begin(rng), boost::end(rng), std::back_inserter(ans));
        BOOST_CHECK( oven::equals(
            rng|scanned(0, pstade::plus)|dropped(1),
            ans
        ) );
    }
    {
        int src[]  = { 1, 2, 3, 4, 5, 6, 7, 8, 9,10};
        int ans1[] = { 0, 1, 3, 6,10,15,21,28,36,45,55};

        BOOST_CHECK( oven::equals(
            src|scanned(0, pstade::plus),
            ans1
        ) );
    }
    {
        std::vector<int> src;
        BOOST_CHECK( distance(src|scanned(10, pstade::plus)) == 1 );
        BOOST_CHECK( value_front(src|scanned(10, pstade::plus)) == 10 );
    }
    {
        int src[] = { 12 };
        BOOST_CHECK( distance(src|scanned(pstade::plus)) == 1 );
        BOOST_CHECK( value_front(src|scanned(pstade::plus)) == 12 );
    }
    {
        int src[] = { 1, 2, 3, 4 };
        int ans[] = { 10, 9, 7, 4, 0 }; 

        BOOST_CHECK( oven::equals(
            src|scanned(10, &::minus),
            ans
        ) );
    }

    {
        int const src[] = { 1,2,3,4,5 };
        std::string null;

        BOOST_FOREACH (std::string str, src|scanned(null, &::stringize)) {
            std::cout << "\"" << str << "\" ";
        }
        // outputs: "" "1" "12" "123" "1234" "12345"
    }
}


int test_main(int, char*[])
{
    ::test();
    return 0;
}
