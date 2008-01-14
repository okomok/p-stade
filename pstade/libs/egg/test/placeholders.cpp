#include <pstade/vodka/drink.hpp>


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/egg/placeholders.hpp>
#include <pstade/minimal_test.hpp>


#include <pstade/egg/detail/substitute.hpp>
#include <boost/utility/addressof.hpp>


namespace egg = pstade::egg;
using namespace egg;


void pstade_minimal_test()
{
    int i1 = 1, i2 = 2, i3 = 3, i4 = 4, i5 = 5;
    BOOST_CHECK(placeholder1(i1, i2, i3, i4, i5) == 1);
    BOOST_CHECK(placeholder1(i1, i2, i3, i4, i5) == 1);
    BOOST_CHECK(placeholder1(i1, i2, i3, i4, i5) == 1);
    BOOST_CHECK(placeholder1(i1, i2, i3, i4, i5) == 1);
    BOOST_CHECK(placeholder1(i1, i2, i3, i4, i5) == 1);

    BOOST_CHECK(placeholder2(i1, i2, i3, i4, i5) == 2);
    BOOST_CHECK(placeholder2(i1, i2, i3, i4, i5) == 2);
    BOOST_CHECK(placeholder2(i1, i2, i3, i4, i5) == 2);
    BOOST_CHECK(placeholder2(i1, i2, i3, i4, i5) == 2);
    BOOST_CHECK(placeholder2(i1, i2, i3, i4, i5) == 2);

    BOOST_CHECK(placeholder1(i1, i2, i3, i4, i5) == 1);
    BOOST_CHECK(placeholder2(i1, i2, i3, i4, i5) == 2);
    BOOST_CHECK(placeholder3(i1, i2, i3, i4, i5) == 3);
    BOOST_CHECK(placeholder4(i1, i2, i3, i4, i5) == 4);
    BOOST_CHECK(placeholder5(i1, i2, i3, i4, i5) == 5);

    {
        using namespace placeholders;

        BOOST_CHECK(_1(1, 2, 3, 4, 5) == 1);
        BOOST_CHECK(_2(1, 2, 3, 4, 5) == 2);
        BOOST_CHECK(_3(1, 2, 3, 4, 5) == 3);
        BOOST_CHECK(_4(1, 2, 3, 4, 5) == 4);
        BOOST_CHECK(_5(1, 2, 3, 4, 5) == 5);
    }

    {
        BOOST_CHECK(detail::substitute(placeholder2)(i1, i2, i3, i4, i5) == 2);
    }
}
