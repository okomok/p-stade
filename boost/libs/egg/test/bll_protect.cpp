

// Boost.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/egg/bll/protect.hpp>
#include "./egg_test.hpp"


#include BOOST_EGG_SUPPRESS_WARNING_BEGIN()
#include <boost/lambda/core.hpp>
#include <boost/lambda/lambda.hpp>
#include BOOST_EGG_SUPPRESS_WARNING_END()


#include "./using_egg.hpp"
namespace bll = boost::lambda;


void egg_test()
{
    {
        int i = 3, j = 9;
        BOOST_CHECK( bll_protect_0(i) == i );
        BOOST_CHECK( bll_protect_0(bll::_1)(i) == i );
        BOOST_CHECK( bll_protect_1(bll::_1)(j)(i) == i );
        BOOST_CHECK( bll_protect_2(bll::_1)(j)(j)(i) == i );
        BOOST_CHECK( bll_protect_3(bll::_1)(j)(j)(j)(i) == i );
    }
}
