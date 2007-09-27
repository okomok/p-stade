#include <pstade/vodka/drink.hpp>


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/egg/infix.hpp>
#include <pstade/egg/apply.hpp>
#include <pstade/minimal_test.hpp>

#include <pstade/egg/negate.hpp>

using namespace pstade::egg;

//[code_infix_apply_example
void test_apply()
{
    using namespace infix;
    BOOST_CHECK(apply(negate, apply(negate, apply(negate, 10))) == -10);

    BOOST_CHECK((negate ^=apply^= 10) == -10);
    BOOST_CHECK((negate ^=apply^= negate ^=apply^= 10) == 10);
    BOOST_CHECK((negate ^=apply^= negate ^=apply^= negate ^=apply^= 10) == -10);
}
//]


void pstade_minimal_test()
{
    ::test_apply();
}
