#include <pstade/vodka/drink.hpp>
#include <boost/test/minimal.hpp>


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/oven/tests.hpp>
#include <pstade/oven/counting_range.hpp>


#include <iterator>
#include <string>
#include <vector>
#include <boost/foreach.hpp>
#include <boost/range.hpp>
#include <pstade/oven/functions.hpp>
#include <pstade/oven/take_while_range.hpp>
#include <pstade/oven/transform_range.hpp>
#include <pstade/oven/regularize_range.hpp>
#include <pstade/result_of_lambda.hpp>
#include <boost/lambda/lambda.hpp>
#include <pstade/reference.hpp>


void test()
{
    namespace oven = pstade::oven;
    using namespace oven;
    
    {
        int ans[] = { 2, 3, 4, 5, 6 };
        std::vector<int> expected = ans|copied;

        BOOST_CHECK( oven::test_RandomAccess_Readable(oven::make_counting_range(2, 7), expected) );
    }

    {
        int ans[] = { 2, 3, 4, 5, 6 };

        BOOST_CHECK( oven::equal(oven::make_counting_range(2, 7), ans) );

        std::vector<int> vec;
        oven::copy(oven::make_counting_range(2, 7), std::back_inserter(vec));
        BOOST_CHECK( oven::equal(vec, ans) );
    }
    {
        int ans[] = { 0, 1, 2, 3, 4 };
        BOOST_CHECK( oven::equal(oven::from_0_to(5), ans) );
    }

    {
        std::vector<int> vec;
        int ans[] = { 0, 1, 2, 3, 4 };

        BOOST_FOREACH (int i, oven::make_counting_range(0, 5)) {
            vec.push_back(i);
        }

        BOOST_CHECK( oven::equal(vec, ans) );
        vec.clear();

        BOOST_FOREACH (int i, oven::from_0_to(5)) {
            vec.push_back(i);
        }

        BOOST_CHECK( oven::equal(vec, ans) );

        std::vector<int>::size_type i = 0;
        BOOST_FOREACH (i, oven::from_0_to(vec.size())) {
            ++i;
        }
        BOOST_CHECK( i == 5 );

        vec.clear();
    }

#if 0 // no longer throw.
    {
        try {
            oven::make_counting_range(100, 2);
        }
        catch (std::range_error& ) {
            return;
        }
        BOOST_CHECK(false);
    }
#endif

    {
        namespace lambda = boost::lambda;

        oven::copy(
            oven::count_from(1)|
                transformed(lambda::_1 * 30)|regularized|
                taken_while(lambda::_1 < 1000),
            oven::to_ostream<int>(std::cout, ",")
        );
    }
}


int test_main(int, char*[])
{
    ::test();
    return 0;
}
