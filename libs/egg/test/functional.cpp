#include <pstade/vodka/drink.hpp>


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/egg/equal_to.hpp>
#include <pstade/egg/greater.hpp>
#include <pstade/egg/less.hpp>
#include <pstade/egg/greater_equal.hpp>
#include <pstade/egg/less_equal.hpp>
#include <pstade/egg/logical_and.hpp>
#include <pstade/egg/logical_or.hpp>
#include <pstade/egg/logical_not.hpp>
#include <pstade/egg/equal_to_0.hpp>
#include <pstade/egg/plus.hpp>
#include <pstade/egg/minus.hpp>
#include <pstade/egg/modulus.hpp>
#include <pstade/egg/divides.hpp>
#include <pstade/egg/multiplies.hpp>
#include <pstade/egg/negate.hpp>
#include <pstade/minimal_test.hpp>


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
    BOOST_CHECK( pstade::egg::logical_not(pstade::egg::equal_to(0, 3)) );

    BOOST_CHECK( pstade::egg::equal_to_0(0) );
    BOOST_CHECK(!pstade::egg::equal_to_0(1) );

    BOOST_CHECK( pstade::egg::plus(3, 1) == 4 );
    BOOST_CHECK( pstade::egg::minus(31, 5) == 26 );
    BOOST_CHECK( pstade::egg::divides(31, 5) == 6 );
    BOOST_CHECK( pstade::egg::modulus(31, 5) == 1 );
    BOOST_CHECK( pstade::egg::multiplies(3, 5) == 15 );

    BOOST_CHECK( pstade::egg::negate(3) == -3 );
}
