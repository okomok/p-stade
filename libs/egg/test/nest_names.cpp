

// Boost.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/egg/nest.hpp>
#include "./egg_test.hpp"


#include <boost/bind.hpp> // placeholders


void egg_test()
{
    using BOOST_EGG_NEST_NAMES;

    (void)_1; (void)_2; (void)_3;
    (void)nest0; (void)nest1; (void)nest2; (void)nest3; (void)nest4; (void)nest5;
    (void)_0_; (void)_1_; (void)_2_; (void)_3_; (void)_4_;

    int i9 = 9;
    // \x -> (\y -> y(x))
    BOOST_CHECK( nest2(_1_(_1))(_0_(_1))(i9)(_1) == 9 );
}
