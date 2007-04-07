#include <pstade/vodka/drink.hpp>
#include <boost/test/minimal.hpp>


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <iostream>
#include <pstade/oven/distance.hpp>
#include <pstade/oven/cycled.hpp>
#include <pstade/oven/foreach.hpp>
#include <pstade/oven/functions.hpp>


using namespace pstade::oven;

void test_hours()
{
    int const clock[] = { 0,1,2,3,4,5,6,7,8,9,10,11 };
    BOOST_CHECK( 8760 == distance(clock|cycled(0, 2)|cycled(0, 365)) );
}


template<class Range>
void print(Range& rng)
{
    typedef typename range_iterator<Range>::type iter_t;
    for (iter_t it = begin(rng), last = end(rng); it != last; ++it) {
        std::cout << "day: " << *it << ", week: " << it.count() << "th" << std::endl;
    }
}

void test_weeks()
{
    int const days[] = { 0,1,2,3,4,5,6 };
    ::print(days|cycled(5, 8));
}


int test_main(int, char*[])
{
    ::test_hours();
    ::test_weeks();
    return 0;
}
