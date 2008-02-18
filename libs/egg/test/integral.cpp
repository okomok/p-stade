#include <pstade/vodka/drink.hpp>


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/egg/integral.hpp>
#include <pstade/minimal_test.hpp>


#include <pstade/result_of.hpp>


using namespace pstade::egg;


void pstade_minimal_test()
{
    unsigned int ui = 0;
    signed int i = 0;

    ui = i|integral();
}
