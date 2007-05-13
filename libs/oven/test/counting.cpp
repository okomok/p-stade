#include <pstade/vodka/drink.hpp>
#include <boost/test/minimal.hpp>


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/oven/tests.hpp>
#include <pstade/oven/counting.hpp>


#include <iterator>
#include <string>
#include <vector>
#include <boost/foreach.hpp>
#include <boost/range.hpp>
#include <pstade/oven/algorithm.hpp>
#include "./core.hpp"
#include <pstade/oven/taken.hpp>
#include <pstade/oven/taken_while.hpp>
#include <pstade/oven/stream_writer.hpp>
#include <pstade/oven/transformed.hpp>
#include <pstade/result_of_lambda.hpp>
#include <boost/lambda/lambda.hpp>
#include <pstade/pack.hpp>


void test()
{
    namespace oven = pstade::oven;
    using namespace oven;
    
    {
        int ans[] = { 2, 3, 4, 5, 6 };
        std::vector<int> expected = ans|copied;

        BOOST_CHECK( oven::test_RandomAccess_Readable(oven::counting(2, 7), expected) );
    }

    {
        int ans[] = { 2, 3, 4, 5, 6 };

        BOOST_CHECK( oven::equal(oven::counting(2, 7), ans) );

        std::vector<int> vec;
        oven::copy(oven::counting(2, 7), std::back_inserter(vec));
        BOOST_CHECK( oven::equal(vec, ans) );
    }
    {
        int ans[] = { 0, 1, 2, 3, 4 };
        BOOST_CHECK( oven::equal(oven::counting(0, 5), ans) );
    }
    {
        int ans[] = { 3,4,5,6,7 };
        BOOST_CHECK( oven::equals(counting(3, max_count)|taken(5), ans) );
    }

    {
        BOOST_CHECK( oven::distance(counting(min_count, 0)|taken(5)) == 5 );
    }
    {
        std::vector<int> vec;
        int ans[] = { 0, 1, 2, 3, 4 };

        BOOST_FOREACH (int i, oven::counting(0, 5)) {
            vec.push_back(i);
        }

        BOOST_CHECK( oven::equal(vec, ans) );
        vec.clear();

        BOOST_FOREACH (int i, oven::counting(0, 5)) {
            vec.push_back(i);
        }

        BOOST_CHECK( oven::equal(vec, ans) );

        std::vector<int>::size_type i = 0;
        BOOST_FOREACH (i, oven::counting(0, vec.size())) {
            ++i;
        }
        BOOST_CHECK( i == 5 );

        vec.clear();
    }

#if 0 // no longer throw.
    {
        try {
            oven::counting(100, 2);
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
            oven::counting(1, oven::max_count)|
                transformed(regular(lambda::_1 * 30))|
                taken_while(regular(lambda::_1 < 1000)),
                std::ostream_iterator<int>(std::cout, ",")
        );
    }
}


int test_main(int, char*[])
{
    ::test();
    return 0;
}
