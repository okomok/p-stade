

// Boost.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/egg/regular.hpp>
#include "./egg_test.hpp"


#include <boost/lambda/lambda.hpp>
#include <boost/lambda/core.hpp>


#include "./using_egg.hpp"


namespace bll = boost::lambda;


template< class F >
void regular_check(F const f)
{
    F f1(f);
    F f2;
    f2 = f1;
}


void egg_test()
{
    {
        ::regular_check(regular(bll::_1 != 'c'));
        ::regular_check(regular(bll::_1 += 1));
    }
}

