#include <pstade/vodka/drink.hpp>
#include <boost/test/minimal.hpp>


// PStade.Wine
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/sarray.hpp>


void test()
{
    using namespace pstade;

    sarray<std::string> sarr0(40);
    sarr0[39] = "abc";
    sarray<std::string> const sarr1(400);
    sarr1[399] = "cde";
}


int test_main(int, char*[])
{
    ::test();
    return 0;
}
