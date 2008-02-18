#include <boost/egg/pstade/vodka/drink.hpp>


// Boost.Egg
//
// Copyright Shunsuke Sogame 2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/egg/detail/functional2.hpp>
#include <boost/egg/pstade/minimal_test.hpp>


void pstade_minimal_test()
{
    BOOST_CHECK( pstade::egg::equal_to(1, 1) );
    BOOST_CHECK(!pstade::egg::equal_to(0, 1) );

    BOOST_CHECK( pstade::egg::greater(3, 0) );
    BOOST_CHECK(!pstade::egg::greater(1, 3) );
    BOOST_CHECK( pstade::egg::less(0, 3) );
    BOOST_CHECK(!pstade::egg::less(3, 1) );

    BOOST_CHECK( pstade::egg::greater_equal(3, 0) );
    BOOST_CHECK( pstade::egg::greater_equal(1, 1) );
    BOOST_CHECK( pstade::egg::less_equal(0, 0) );
    BOOST_CHECK( pstade::egg::less_equal(0, 1) );

    BOOST_CHECK( pstade::egg::logical_and(pstade::egg::equal_to(0, 0), pstade::egg::greater(3, 0)) );
    BOOST_CHECK( pstade::egg::logical_or(pstade::egg::equal_to(0, 3), pstade::egg::greater(3, 0)) );

    BOOST_CHECK( pstade::egg::plus(3, 1) == 4 );
    BOOST_CHECK( pstade::egg::minus(31, 5) == 26 );
    BOOST_CHECK( pstade::egg::divides(31, 5) == 6 );
    BOOST_CHECK( pstade::egg::modulus(31, 5) == 1 );
    BOOST_CHECK( pstade::egg::multiplies(3, 5) == 15 );
}
