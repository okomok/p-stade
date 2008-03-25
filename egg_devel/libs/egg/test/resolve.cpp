

// Boost.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/egg/resolve.hpp>
#include "./egg_test.hpp"


#include "./using_egg.hpp"


void foo(char *) {}
int foo(int i) { return i; }

struct my
{
    void bar(char *) {}
    int bar(int i) const { return i; }
};

void egg_test()
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
