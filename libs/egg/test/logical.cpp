#include <boost/egg/pstade/vodka/drink.hpp>


// Boost.Egg
//
// Copyright Shunsuke Sogame 2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/egg/functional.hpp>
#include <boost/egg/pstade/minimal_test.hpp>


namespace egg = pstade::egg;
using namespace egg;


void pstade_minimal_test()
{
    BOOST_CHECK( logical_and(10 ,20) );
    BOOST_CHECK( !logical_and(10 ,0) );
    BOOST_CHECK( logical_or(10 ,20) );
    BOOST_CHECK( !logical_not(10) );
    BOOST_CHECK( logical_not(0) );
}
