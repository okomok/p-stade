

// Boost.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/egg/placeholders.hpp>
#include "./egg_test.hpp"


#include <boost/egg/detail/substitute.hpp>
#include <boost/utility/addressof.hpp>


#include "./using_egg.hpp"


void egg_test()
{
    {
        using namespace placeholders;

        BOOST_CHECK(_1(1, 2, 3, 4, 5) == 1);
        BOOST_CHECK(_2(1, 2, 3, 4, 5) == 2);
        BOOST_CHECK(_3(1, 2, 3, 4, 5) == 3);
        BOOST_CHECK(_4(1, 2, 3, 4, 5) == 4);
        BOOST_CHECK(_5(1, 2, 3, 4, 5) == 5);
    }

    {
        int i1 = 1, i2 = 2, i3 = 3, i4 = 4, i5 = 5;
        BOOST_CHECK(detail::substitute(X_arg<2>())(i1, i2, i3, i4, i5) == 2);
        BOOST_CHECK(detail::substitute(placeholders::_2)(i1, i2, i3, i4, i5) == 2);
    }
}
