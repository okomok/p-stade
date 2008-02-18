

// Boost.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/egg/curry.hpp>
#include "./egg_test.hpp"


#include <boost/function.hpp>
#include <boost/egg/functional.hpp> // plus


void egg_test()
{
    namespace egg = pstade::egg;
    using namespace egg;

    boost::function<int(int)> f = curry2(plus)(1);
    BOOST_CHECK( f(2) == 3 );
}
