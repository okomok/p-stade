#include <pstade/vodka/drink.hpp>
#include <boost/test/minimal.hpp>


// PStade.Oven
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/oven/scan_range.hpp>


#include <iostream>
#include <iterator>
#include <string>
#include <vector>
#include <boost/foreach.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/range.hpp>
#include <pstade/oven/functions.hpp>


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
    using namespace pstade;
    using namespace oven;

    {
        int src[]  = { 1, 2, 3, 4, 5, 6, 7, 8, 9,10};
        int ans1[] = { 1, 3, 6,10,15,21,28,36,45,55};

        BOOST_CHECK( oven::equals(
            src|scanned(0),
            ans1
        ) );
    }

    {
        int src[] = { 1, 2, 3, 4 };
        int ans[] = { 9, 7, 4, 0 }; 

        BOOST_CHECK( oven::equals(
            src|scanned(10, ::minus),
            ans
        ) );

        BOOST_CHECK( oven::equals(
            src|scanned(10, &::minus),
            ans
        ) );
    }

    {
        int const src[] = { 1,2,3,4,5 };

        BOOST_FOREACH (std::string str, src|scanned(std::string(), ::stringize)) {
            std::cout << "\"" << str << "\" ";
        }
        // outputs: "1" "12" "123" "1234" "12345"
    }
}


int test_main(int, char*[])
{
    ::test();
    return 0;
}
