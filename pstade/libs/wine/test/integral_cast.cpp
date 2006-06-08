#include <pstade/vodka/drink.hpp>
#include <boost/test/minimal.hpp>


// PStade.Wine
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/integral_cast.hpp>


void test()
{
    using namespace pstade;

    unsigned int ui = 0;
    signed int i = 0;

    ui = pstade::integral_cast<signed int>(i);

    ui = pstade::integral(i);
    ui = pstade::integral(3);
}


int test_main(int, char*[])
{
    ::test();
    return 0;
}
