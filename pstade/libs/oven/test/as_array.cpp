#include <pstade/vodka/drink.hpp>
#include <boost/test/minimal.hpp>


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/oven/as_array.hpp>


#include <iterator>
#include <string>
#include <boost/range.hpp>
#include <pstade/oven/distance.hpp>


void test()
{
    namespace oven = pstade::oven;
    using namespace oven;

    {
        char str[] = "hello range";
        BOOST_CHECK( oven::distance(str|as_array) == 12 );
    }
}


int test_main(int, char*[])
{
    ::test();
    return 0;
}
