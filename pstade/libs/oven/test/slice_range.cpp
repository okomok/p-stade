#include <pstade/vodka/drink.hpp>
#include <boost/test/minimal.hpp>


// PStade.Oven
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/oven/slice_range.hpp>


#include <string>
#include <vector>
#include <pstade/oven/equal.hpp>


void test()
{
    using namespace pstade;
    using namespace oven;

    std::string src("0123456");

    {
        BOOST_CHECK( oven::equals(oven::make_slice_range(src, 0, 0), src) );
    }

    {
        BOOST_CHECK( oven::equals(src|sliced(1, -1), std::string("12345")) );
    }
}


int test_main(int, char*[])
{
    ::test();
    return 0;
}
