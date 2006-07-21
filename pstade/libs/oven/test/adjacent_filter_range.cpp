#include <pstade/vodka/drink.hpp>
#include <boost/test/minimal.hpp>


// PStade.Oven
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/oven/adjacent_filter_range.hpp>


#include <iterator>
#include <string>
#include <vector>
#include <boost/foreach.hpp>
#include <boost/range.hpp>
#include <boost/range/concepts.hpp>
#include <pstade/oven/functions.hpp>
#include <pstade/oven/reverse_range.hpp>
#include <pstade/oven/istream_range.hpp>


struct is_not_divisor
{
    bool operator()(int x, int y) const { return (y % x) != 0; }
};


struct not_equal_to
{
    bool operator()(int x, int y) const { return x != y; }
};


void test()
{
    using namespace pstade;
    using namespace oven;

    int src[] = { 2, 2, 4, 4, 6, 8, 8, 10, 10, 20, 40, 80, 120 };
    int ans1[] = { 2, 6, 8, 10, 120 };
    int ans2[] = { 2, 4, 6, 8, 10, 20, 40, 80, 120 };
    int ans3[] = { 2, 8, 10 };

    {
        typedef adjacent_filter_range< std::string, is_not_divisor > rng_t;
        boost::function_requires< boost::BidirectionalRangeConcept<rng_t> >();
    }

    {
        BOOST_CHECK((
            oven::equals( oven::make_adjacent_filter_range(src, is_not_divisor()), ans1)
        ));

        BOOST_CHECK((
            oven::equals( oven::make_adjacent_filter_range(src, not_equal_to()), ans2)
        ));
    }

    {
        BOOST_CHECK((
            oven::equals(
                src |
                    oven::adjacent_filtered(is_not_divisor()) |
                    oven::adjacent_filtered(is_not_divisor()),
                ans3
            )
        ));
    }

    {
        BOOST_CHECK((
            oven::equals( src|adjacent_filtered(is_not_divisor())|reversed|reversed, ans1)
        ));

        BOOST_FOREACH (int i, src|adjacent_filtered(is_not_divisor())|reversed)  {
            std::cout << i << ',';
        }
    }

    //std::stringstream ss;
    //oven::make_istream_range<int>(ss)|adjacent_filtered(is_not_divisor());
}


int test_main(int, char*[])
{
    ::test();
    return 0;
}
