

// Boost.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/egg/flip.hpp>
#include <boost/egg/curry.hpp>
#include <boost/egg/uncurry.hpp>


#include "./egg_example.hpp"


int bar_(int i0, int i1, int i2, int i3)
{
    return (i0 - i1) + (i2 - i3);
}

result_of_curry4<int(*)(int, int, int, int)>::type
    const bar = BOOST_EGG_CURRY4(&bar_);


void egg_example()
{
    BOOST_CHECK( flip(uncurry(bar))(1, 2)(3)(4) == (2 - 1) + (3 - 4) );
    BOOST_CHECK( curry2(flip(uncurry(bar)))(1)(2)(3)(4) == (2 - 1) + (3 - 4) );
}
