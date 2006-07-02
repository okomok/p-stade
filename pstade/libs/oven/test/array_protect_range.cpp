#include <pstade/vodka/drink.hpp>
#include <boost/test/minimal.hpp>


// PStade.Oven
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/oven/array_protect_range.hpp>


#include <iterator>
#include <string>
#include <boost/range.hpp>
#include <pstade/oven/distance.hpp>


void test()
{
    using namespace pstade;
    using namespace oven;

    {
        char str[] = "hello range";

        BOOST_CHECK( oven::distance(oven::make_array_protect_range(str)) == 12 );
        BOOST_CHECK( oven::distance(str|oven::array_protected) == 12 );
    }
}


int test_main(int, char*[])
{
    ::test();
    return 0;
}
