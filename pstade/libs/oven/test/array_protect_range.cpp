#include <pstade/vodka/drink.hpp>
#include <boost/test/minimal.hpp>


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
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
    namespace oven = pstade::oven;
    using namespace oven;

    {
        char const str[] = "hello range";

        array_protect_range< char const [12] > rng(str);
        BOOST_CHECK( oven::distance(rng) == 12 );
        BOOST_CHECK( oven::distance(oven::make_array_protect_range(str)) == 12 );
        BOOST_CHECK( oven::distance(str|array_protected) == 12 );
    }
}


int test_main(int, char*[])
{
    ::test();
    return 0;
}
