#include <pstade/vodka/drink.hpp>
#include <boost/test/minimal.hpp>


// PStade.Wine
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/in_out.hpp>
#include <pstade/unused.hpp>


void foo(int& o, int i)
{
    pstade::unused(o, i);
}


void test()
{
    using namespace pstade;
    int o = 3;
    ::foo(out(o), in(3));
}


int test_main(int, char*[])
{
    ::test();
    return 0;
}
