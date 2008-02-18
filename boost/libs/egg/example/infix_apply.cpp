

// Boost.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/egg/infix.hpp>
#include <boost/egg/apply.hpp>
#include "../test/egg_test.hpp"

#include <boost/egg/functional.hpp> // negate, plus
#include <boost/egg/lazy.hpp>
#include <boost/egg/bll/placeholders.hpp>
#include <boost/lambda/lambda.hpp>
#include <boost/egg/bll/result_of.hpp>
#include <functional>


using namespace boost::egg;

void test_apply()
{
    using namespace infix;

    //[code_infix_apply_example
    BOOST_CHECK(apply(negate, apply(negate, apply(negate, 10))) == -10);
    //]
#if 0 // right-to-left; rejected
    BOOST_CHECK((negate ^=apply^= 10) == -10);
    BOOST_CHECK((negate ^=apply^= negate ^=apply^= 10) == 10);
    BOOST_CHECK((negate ^=apply^= negate ^=apply^= negate ^=apply^= 10) == -10);
#endif
    //[code_infix_plus_example
    std::plus<int> my_plus;
    BOOST_CHECK( (1 ^my_plus^ 2) == 3 );
    //]

    {
#if 0 // doesn't work cuz operator^ is overloaded.
        std::plus<int> my_plus;
        int one = 1;
        BOOST_CHECK( (bll_1 ^lazy(my_plus)^ 2)(one) == 3 );
#endif 
    }
}


void egg_test()
{
    ::test_apply();
}
