#include <pstade/vodka/drink.hpp>


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/egg/automatic.hpp>
#include <pstade/minimal_test.hpp>


#include <pstade/egg/construct.hpp>
#include <pstade/egg/by_value.hpp>
#include <pstade/egg/const.hpp>
#include <memory>


namespace egg = pstade::egg;
using namespace egg;


typedef automatic<X_construct<mpl_1, mpl_2>, by_value>::type T_value_constructor;
PSTADE_EGG_CONST((T_value_constructor), value_constructor) = PSTADE_EGG_AUTOMATIC();


void pstade_minimal_test()
{
    {
        // how to test?
        int i = value_constructor(3);
        BOOST_CHECK(i == 3);
    }
}
