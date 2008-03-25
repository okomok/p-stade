

// Boost.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/egg/detail/eat_mutable.hpp>
#include "./egg_test.hpp"


void egg_test()
{
    {
        int BOOST_EGG_EAT_MUTABLE(mutable) i = 3;
        (void)i;
    }
    {
        int BOOST_EGG_EAT_MUTABLE(const) i = 3;
        (void)i;
    }
    {
        int BOOST_EGG_EAT_MUTABLE(volatile) i = 3;
        (void)i;
    }
    {
        int BOOST_EGG_EAT_MUTABLE(volatile const) i = 3;
        (void)i;
    }
    {
        int BOOST_EGG_EAT_MUTABLE(const volatile) i = 3;
        (void)i;
    }
}
