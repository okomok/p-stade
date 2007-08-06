#include <pstade/vodka/drink.hpp>


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/egg/lambda_unlambda.hpp>
#include <pstade/egg/lambda_bind.hpp>
#include <pstade/egg/lambda_placeholders.hpp>
#include <pstade/result_of_lambda.hpp>
#include <pstade/minimal_test.hpp>


#include <pstade/result_of.hpp>
#include <pstade/egg/plus.hpp>
#include <pstade/egg/to_ref.hpp>
#include <pstade/test.hpp>


using namespace pstade::egg;


int sum_of_args_1(int a) { return a; }

void pstade_minimal_test()
{
    {
        pstade::result_of<op_lambda_bind(op_plus, op_lambda_1, int)>::type b =
            lambda_bind(plus, lambda_1, 10);

        BOOST_CHECK( b(20|to_ref) == 30 );
    }
    {
        typedef
            pstade::result_of<op_lambda_bind(int (*)(int), int)>::type
        b_t;

        b_t b = lambda_bind(&sum_of_args_1, 10);

        PSTADE_TEST_IS_RESULT_OF((int), b_t())

        pstade::result_of<b_t()>::type b_ = b();
        BOOST_CHECK(b_ == 10);
    }
    {
        op_plus f = lambda_unlambda(plus); // no effect
        BOOST_CHECK( f(1,2) == 3 );

        // unlambda it!
        pstade::result_of<op_lambda_unlambda(op_lambda_1)>::type u = lambda_unlambda(lambda_1);
        int i = 10;
        BOOST_CHECK( boost::lambda::bind(u, lambda_1)(i) == 10 );
    }
}
