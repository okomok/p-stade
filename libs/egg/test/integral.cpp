

// Boost.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/egg/integral.hpp>
#include "./egg_test.hpp"


#include <boost/egg/result_of.hpp>


using namespace boost::egg;


void egg_test()
{
    {
        unsigned int ui = 0;
        signed int i = 0;

        ui = i|integral();
    }
    {
        unsigned int ui = 0;
        signed int i = 0;

        ui = X_integral_cast<signed int>()(i);
        ui = integral_cast<signed int>(i);
    }
}
