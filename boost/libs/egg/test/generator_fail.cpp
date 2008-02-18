#include <pstade/vodka/drink.hpp>


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// error message check.


#include <pstade/egg/generator.hpp>
#include <pstade/minimal_test.hpp>


#include <pstade/egg/const.hpp>
#include <memory>


namespace egg = pstade::egg;
using namespace egg;


typedef
    generator<
        std::pair< deduce<mpl_1, as_value>, deduce<mpl_2, as_value> >
    >::type
T_make_pair;

PSTADE_EGG_CONST((T_make_pair), make_pair) = {{}};


void pstade_minimal_test()
{
    make_pair(1);
}
