#include <pstade/vodka/drink.hpp>


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/egg/compose.hpp>
#include <pstade/egg/infix.hpp>
#include <pstade/minimal_test.hpp>


using namespace pstade::egg;

// `&` needed for msvc ICE workaround.

//[code_example_composing
int increment(int i)
{
    return i + 1;
}

int decrement(int i)
{
    return i - 1;
}

void test()
{
    using namespace infix;
    int r = (&increment ^compose^ &decrement ^compose^ &increment)(3);
    BOOST_CHECK( r == 4 );
}
//]


void pstade_minimal_test()
{
    test();
}
