

// Boost.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/egg/detail/fake.hpp>
#include "./egg_test.hpp"


using boost::egg::details::fake;


struct A {};

void egg_test()
{
    bool b = false;
    if (b)
        fake<int>();
    if (b)
        fake<A>();
    if (b)
        fake<A&>();
}
