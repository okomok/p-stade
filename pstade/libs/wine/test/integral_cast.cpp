#include <pstade/vodka/drink.hpp>
#include <boost/test/minimal.hpp>


// PStade.Wine
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/integral_cast.hpp>


void test()
{
    using namespace pstade;

    unsigned int ui = 0;
    signed int i = 0;

    ui = pstade::op_integral_cast<signed int>()(i);
    ui = pstade::integral_cast<signed int>(i);

    //ui = pstade::integral(i);
    //ui = pstade::integral(3);

    ui = i|to_integer;
}


int test_main(int, char*[])
{
    ::test();
    return 0;
}
