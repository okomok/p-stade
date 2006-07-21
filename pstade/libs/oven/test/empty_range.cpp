#include <pstade/vodka/drink.hpp>
#include <boost/test/minimal.hpp>


// PStade.Oven
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/oven/empty_range.hpp>


#include <boost/range/empty.hpp>
#include <pstade/oven/functions.hpp>


void test()
{
    using namespace pstade;
    using namespace oven;

    {
        BOOST_CHECK( boost::empty( empty_range<int>() ) );
        BOOST_CHECK( oven::equals( empty_range<char>(), empty_range<char>() ) );
    }
}


int test_main(int, char*[])
{
    ::test();
    return 0;
}
