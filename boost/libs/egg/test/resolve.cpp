#include <pstade/vodka/drink.hpp>


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/egg/resolve.hpp>
#include <pstade/minimal_test.hpp>


namespace egg = pstade::egg;
using namespace egg;


void foo(char *) {}
int foo(int i) { return i; }

struct my
{
    void bar(char *) {}
    int bar(int i) const { return i; }
};

void pstade_minimal_test()
{
    {
        X_resolve<void(char *)>()(foo);
        BOOST_CHECK( egg::resolve<int(int)>(foo)(10) == 10);
    }
    {
        my m;
        X_resolve<void(my::*)(char*)>()(&my::bar);
        BOOST_CHECK( (m.*egg::resolve<int(my::*)(int) const>(&my::bar))(10) == 10);
    }
}
