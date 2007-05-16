#include <pstade/vodka/drink.hpp>
#include <boost/test/minimal.hpp>


// PStade.Wine
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/fuse.hpp>


int my_plus(int x, int y, int z)
{
    return x + y + z;
}

int my_two()
{
    return 2;
}


void test()
{
    using namespace pstade;

    {
        BOOST_CHECK(
            pstade::fuse(&::my_plus)(boost::make_tuple(5, 7, 2)) == 14
        );
    }
    {
        BOOST_CHECK(
            pstade::fuse(&::my_two)(boost::make_tuple()) == 2
        );
    }
}


int test_main(int, char*[])
{
    ::test();
    return 0;
}
