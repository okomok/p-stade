

// Boost.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/egg/detail/unused.hpp>
#include "./egg_test.hpp"


void foo(int x)
{
    BOOST_EGG_IGNORE_UNUSED(x);
}

int const BOOST_EGG_UNUSED(y) = 0;


void egg_test()
{
    ::foo(3);
}
