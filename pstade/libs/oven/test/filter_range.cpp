#include <pstade/vodka/drink.hpp>
#include <boost/test/minimal.hpp>


// PStade.Oven
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/oven/filter_range.hpp>


#include <iterator>
#include <string>
#include <vector>
#include <boost/foreach.hpp>
#include <boost/range.hpp>
#include <pstade/oven/algorithms.hpp>


struct is_positive
{
    bool operator()(int x) const { return 0 < x; }
};


struct is_even
{
    bool operator()(int x) const { return (x % 2) == 0; }
};


void test()
{
    using namespace pstade;
    using namespace oven;

    int src[] = { 0, -1, 4, -3, 5, 8, -2 };
    int ans1[] = { 4, 5, 8 };
    int ans2[] = { 4, 8 };

    {
        BOOST_CHECK((
            oven::equal( oven::make_filter_range(src, is_positive()), ans1)
        ));
    }

    {
        BOOST_CHECK((
            oven::equal(
                src |
                    oven::filtered(is_positive()) |
                    oven::filtered(is_even()),
                ans2
            )
        ));
    }
}


int test_main(int, char*[])
{
    ::test();
    return 0;
}
