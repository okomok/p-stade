#include <pstade/vodka/drink.hpp>
#include <boost/test/minimal.hpp>


// PStade.Oven
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/oven/counting_range.hpp>


#include <iterator>
#include <string>
#include <vector>
#include <boost/foreach.hpp>
#include <boost/range.hpp>
#include <pstade/oven/copy.hpp>
#include <pstade/oven/equal.hpp>


void test()
{
    using namespace pstade;
    using namespace oven;

    {
        int ans[] = { 2, 3, 4, 5, 6 };

        BOOST_CHECK( oven::equal(oven::make_counting_range(2, 7), ans) );

        std::vector<int> vec;
        oven::copy(oven::make_counting_range(2, 7), std::back_inserter(vec));
        BOOST_CHECK( oven::equal(vec, ans) );
    }
    {
        int ans[] = { 0, 1, 2, 3, 4 };
        BOOST_CHECK( oven::equal(oven::zero_to(5), ans) );
    }

    {
        std::vector<int> vec;
        int ans[] = { 0, 1, 2, 3, 4 };

        BOOST_FOREACH (int i, oven::make_counting_range(0, 5)) {
            vec.push_back(i);
        }

        BOOST_CHECK( oven::equal(vec, ans) );
        vec.clear();

        BOOST_FOREACH (int i, oven::zero_to(5)) {
            vec.push_back(i);
        }

        BOOST_CHECK( oven::equal(vec, ans) );

        std::vector<int>::size_type i = 0;
        BOOST_FOREACH (i, oven::zero_to(vec.size())) {
            ++i;
        }
        BOOST_CHECK( i == 5 );

        vec.clear();
    }

    {
        try {
            oven::make_counting_range(100, 2);
        }
        catch (std::range_error& ) {
            return;
        }
        BOOST_CHECK(false);
    }
}


int test_main(int, char*[])
{
    ::test();
    return 0;
}
