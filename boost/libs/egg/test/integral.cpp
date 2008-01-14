#include <boost/egg/pstade/vodka/drink.hpp>


// Boost.Egg
//
// Copyright Shunsuke Sogame 2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/egg/integral.hpp>
#include <boost/egg/pstade/minimal_test.hpp>


#include <boost/egg/pstade/result_of.hpp>


using namespace pstade::egg;


void pstade_minimal_test()
{
    unsigned int ui = 0;
    signed int i = 0;

    ui = i|integral();
}
