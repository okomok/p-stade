

// Boost.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/egg/arg.hpp>
#include "./egg_test.hpp"


#include "./using_egg.hpp"


void egg_test()
{
    int i1 = 1, i2 = 2, i3 = 3, i4 = 4, i5 = 5;
    BOOST_CHECK(X_arg<1>()(i1, i2, i3, i4, i5) == 1);
    BOOST_CHECK(X_arg<1>()(i1, i2, i3, i4, i5) == 1);
    BOOST_CHECK(X_arg<1>()(i1, i2, i3, i4, i5) == 1);
    BOOST_CHECK(X_arg<1>()(i1, i2, i3, i4, i5) == 1);
    BOOST_CHECK(X_arg<1>()(i1, i2, i3, i4, i5) == 1);

    BOOST_CHECK(X_arg<2>()(i1, i2, i3, i4, i5) == 2);
    BOOST_CHECK(X_arg<2>()(i1, i2, i3, i4, i5) == 2);
    BOOST_CHECK(X_arg<2>()(i1, i2, i3, i4, i5) == 2);
    BOOST_CHECK(X_arg<2>()(i1, i2, i3, i4, i5) == 2);
    BOOST_CHECK(X_arg<2>()(i1, i2, i3, i4, i5) == 2);

    BOOST_CHECK(X_arg<1>()(i1, i2, i3, i4, i5) == 1);
    BOOST_CHECK(X_arg<2>()(i1, i2, i3, i4, i5) == 2);
    BOOST_CHECK(X_arg<3>()(i1, i2, i3, i4, i5) == 3);
    BOOST_CHECK(X_arg<4>()(i1, i2, i3, i4, i5) == 4);
    BOOST_CHECK(X_arg<5>()(i1, i2, i3, i4, i5) == 5);
}
