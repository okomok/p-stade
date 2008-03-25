

// Boost.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/egg/detail/functional2.hpp>
#include "./egg_test.hpp"


void egg_test()
{
    BOOST_CHECK( boost::egg::equal_to(1, 1) );
    BOOST_CHECK(!boost::egg::equal_to(0, 1) );

    BOOST_CHECK( boost::egg::greater(3, 0) );
    BOOST_CHECK(!boost::egg::greater(1, 3) );
    BOOST_CHECK( boost::egg::less(0, 3) );
    BOOST_CHECK(!boost::egg::less(3, 1) );

    BOOST_CHECK( boost::egg::greater_equal(3, 0) );
    BOOST_CHECK( boost::egg::greater_equal(1, 1) );
    BOOST_CHECK( boost::egg::less_equal(0, 0) );
    BOOST_CHECK( boost::egg::less_equal(0, 1) );

    BOOST_CHECK( boost::egg::logical_and(boost::egg::equal_to(0, 0), boost::egg::greater(3, 0)) );
    BOOST_CHECK( boost::egg::logical_or(boost::egg::equal_to(0, 3), boost::egg::greater(3, 0)) );

    BOOST_CHECK( boost::egg::plus(3, 1) == 4 );
    BOOST_CHECK( boost::egg::minus(31, 5) == 26 );
    BOOST_CHECK( boost::egg::divides(31, 5) == 6 );
    BOOST_CHECK( boost::egg::modulus(31, 5) == 1 );
    BOOST_CHECK( boost::egg::multiplies(3, 5) == 15 );

    {
        int a[] = {0,1,2};
        BOOST_CHECK( boost::egg::subscript(a, 2) == 2 );
    }
}
