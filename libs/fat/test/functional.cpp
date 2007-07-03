#include <pstade/vodka/drink.hpp>


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/fat/equal_to.hpp>
#include <pstade/fat/greater.hpp>
#include <pstade/fat/less.hpp>
#include <pstade/fat/greater_equal.hpp>
#include <pstade/fat/less_equal.hpp>
#include <pstade/fat/logical_and.hpp>
#include <pstade/fat/logical_or.hpp>
#include <pstade/fat/logical_not.hpp>
#include <pstade/fat/equal_to_0.hpp>
#include <pstade/fat/plus.hpp>
#include <pstade/fat/minus.hpp>
#include <pstade/fat/modulus.hpp>
#include <pstade/fat/divides.hpp>
#include <pstade/fat/multiplies.hpp>
#include <pstade/fat/negate.hpp>
#include <pstade/minimal_test.hpp>


void pstade_minimal_test()
{
    BOOST_CHECK( pstade::fat::equal_to(1, 1) );
    BOOST_CHECK(!pstade::fat::equal_to(0, 1) );

    BOOST_CHECK( pstade::fat::greater(3, 0) );
    BOOST_CHECK(!pstade::fat::greater(1, 3) );
    BOOST_CHECK( pstade::fat::less(0, 3) );
    BOOST_CHECK(!pstade::fat::less(3, 1) );

    BOOST_CHECK( pstade::fat::greater_equal(3, 0) );
    BOOST_CHECK( pstade::fat::greater_equal(1, 1) );
    BOOST_CHECK( pstade::fat::less_equal(0, 0) );
    BOOST_CHECK( pstade::fat::less_equal(0, 1) );

    BOOST_CHECK( pstade::fat::logical_and(pstade::fat::equal_to(0, 0), pstade::fat::greater(3, 0)) );
    BOOST_CHECK( pstade::fat::logical_or(pstade::fat::equal_to(0, 3), pstade::fat::greater(3, 0)) );
    BOOST_CHECK( pstade::fat::logical_not(pstade::fat::equal_to(0, 3)) );

    BOOST_CHECK( pstade::fat::equal_to_0(0) );
    BOOST_CHECK(!pstade::fat::equal_to_0(1) );

    BOOST_CHECK( pstade::fat::plus(3, 1) == 4 );
    BOOST_CHECK( pstade::fat::minus(31, 5) == 26 );
    BOOST_CHECK( pstade::fat::divides(31, 5) == 6 );
    BOOST_CHECK( pstade::fat::modulus(31, 5) == 1 );
    BOOST_CHECK( pstade::fat::multiplies(3, 5) == 15 );

    BOOST_CHECK( pstade::fat::negate(3) == -3 );
}
