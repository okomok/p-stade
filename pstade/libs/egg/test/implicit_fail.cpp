#include <pstade/vodka/drink.hpp>


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/egg/implicit.hpp>
#include <pstade/minimal_test.hpp>


#include <pstade/egg/by_value.hpp>
#include <pstade/egg/construct.hpp>


namespace egg = pstade::egg;
using namespace egg;


typedef implicit< X_construct<>, by_value >::type T_constructor_by_value;
PSTADE_POD_CONSTANT((T_constructor_by_value), constructor_by_value) = PSTADE_EGG_IMPLICIT();


struct A
{
    A(int) {}
};


struct B
{
    B(int&) {}
};


void pstade_minimal_test()
{
    A a = constructor_by_value(3); // ok.
    (void)a;

    B b = constructor_by_value(3); // should not compile,
    (void)b;
}
