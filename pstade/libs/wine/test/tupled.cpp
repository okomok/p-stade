#include <pstade/vodka/drink.hpp>
#include <boost/test/minimal.hpp>


// PStade.Wine
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/tupled.hpp>


int my_plus(int x, int y, int z)
{
    return x + y + z;
}


void test()
{
    using namespace pstade;

    {
        BOOST_CHECK(
            pstade::tupled(&::my_plus)(boost::make_tuple(5, 7, 2)) == 14
        );
        BOOST_CHECK(
            (&::my_plus|to_tupled)(boost::make_tuple(5, 7, 2)) == 14
        );
    }
}


int test_main(int, char*[])
{
    ::test();
    return 0;
}
