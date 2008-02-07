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

#include <pstade/egg/functional.hpp> // negate, plus
#include <pstade/egg/lazy.hpp>
#include <pstade/egg/bll/placeholders.hpp>
#include <boost/lambda/lambda.hpp>
#include <functional>


using namespace pstade::egg;

void test_apply()
{
    using namespace infix;

    //[code_infix_apply_example
    BOOST_CHECK(apply(negate, apply(negate, apply(negate, 10))) == -10);
    //]
#if 0 // rejected
    BOOST_CHECK((negate ^=apply^= 10) == -10);
    BOOST_CHECK((negate ^=apply^= negate ^=apply^= 10) == 10);
    BOOST_CHECK((negate ^=apply^= negate ^=apply^= negate ^=apply^= 10) == -10);
#endif
    //[code_infix_plus_example
    std::plus<int> my_plus;
    BOOST_CHECK( (1 ^my_plus^ 2) == 3 );
    //]
}


void pstade_minimal_test()
{
    ::test_apply();
}
