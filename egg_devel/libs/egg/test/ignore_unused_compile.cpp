

// Boost.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/egg/detail/ignore_unused.hpp>
#include "./egg_test.hpp"


void foo(int x)
{
    BOOST_EGG_IGNORE_UNUSED(x);
}

void bar(int s0, int s1, int s2)
{
    BOOST_EGG_IGNORE_UNUSED_PARAMS(3, s)
}

void egg_test()
{
    ::foo(3);
    ::bar(1,2,3);
}
