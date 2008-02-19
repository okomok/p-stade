

// Boost.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/egg/implicit.hpp>
#include "./egg_test.hpp"


#include <boost/egg/construct.hpp>
#include <boost/egg/by_value.hpp>
#include <boost/egg/const.hpp>
#include <memory>


#include "./using_egg.hpp"
namespace mpl = boost::mpl;


typedef implicit<X_construct<mpl::_1, mpl::_2>, by_value>::type T_value_constructor;
BOOST_EGG_CONST((T_value_constructor), value_constructor) = BOOST_EGG_IMPLICIT();


void egg_test()
{
    {
        // how to test?
        int i = value_constructor(3);
        BOOST_CHECK(i == 3);
    }
}
