

// Boost.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/egg/if_else.hpp>
#include "./egg_test.hpp"


#include <boost/egg/lazy.hpp>
#include "./using_egg.hpp"

#include BOOST_EGG_SUPPRESS_WARNING_BEGIN()
#include <boost/lambda/lambda.hpp>
#include <boost/lambda/core.hpp>
#include BOOST_EGG_SUPPRESS_WARNING_END()

namespace bll = boost::lambda;


void egg_test()
{
    {
        BOOST_CHECK(if_else_(true, 1, 2) == 1);
        BOOST_CHECK(if_else_(false, 1, 2) == 2);
    }
    {
        int i1 = 1, i2 = 2;
        BOOST_CHECK(lazy(if_else_)(bll::_1 == bll::_2, bll::_1, bll::_2)(i1, i2) == 2);
        BOOST_CHECK(lazy(if_else_)(bll::_1 == bll::_2, bll::_1, bll::_2)(i1, i1) == 1);
    }
}
