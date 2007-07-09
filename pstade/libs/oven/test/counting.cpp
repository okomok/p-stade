#include "./prefix.hpp"
#include <pstade/vodka/drink.hpp>
#define PSTADE_CONCEPT_CHECK


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/oven/counting.hpp>
#include <pstade/minimal_test.hpp>
#include "./detail/test.hpp"


#include <iterator>
#include <string>
#include <vector>
#include <boost/foreach.hpp>
#include <boost/range.hpp>
#include <pstade/oven/algorithm.hpp>
#include <pstade/oven/equals.hpp>
#include <pstade/oven/taken.hpp>
#include <pstade/oven/copied.hpp>
#include <pstade/oven/regular.hpp>
#include <pstade/oven/distance.hpp>
#include <pstade/oven/taken_while.hpp>
#include <pstade/oven/stream_writer.hpp>
#include <pstade/oven/transformed.hpp>
#include <pstade/result_of_lambda.hpp>
#include <boost/lambda/lambda.hpp>


void pstade_minimal_test()
{
    namespace oven = pstade::oven;
    using namespace oven;
    
    {
        int ans[] = { 2, 3, 4, 5, 6 };
        std::vector<int> expected = ans|copied;

        test::random_access_constant(oven::counting(2, 7), expected);
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
