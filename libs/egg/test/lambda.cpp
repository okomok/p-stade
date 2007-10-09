#include <pstade/vodka/drink.hpp>


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/egg/lambda/unlambda.hpp>
#include <pstade/egg/lambda/bind.hpp>
#include <pstade/egg/lambda/placeholders.hpp>
#include <pstade/result_of_lambda.hpp>
#include <pstade/minimal_test.hpp>


#include <pstade/egg/lazy.hpp>
#include <pstade/result_of.hpp>
#include <pstade/egg/plus.hpp>
#include <pstade/egg/to_ref.hpp>
#include <pstade/test.hpp>


using namespace pstade::egg;


int sum_of_args_1(int a) { return a; }

int my_minus(int i, int j) { return i - j; }

int big_arity(int, int, int, int, int, int, int, int, int)
{
    return 3;
}

void pstade_minimal_test()
{
    {
        pstade::result_of<T_lambda_bind(T_plus, T_lambda_1, int)>::type b =
            lambda_bind(plus, lambda_1, 10);

        BOOST_CHECK( b(20|to_ref) == 30 );
        BOOST_CHECK( lambda_bind(&big_arity, 1,2,3,4,lambda_1,6,lambda_2,8,9)(3|to_ref, 4|to_ref) == 3 );
    }
    {
        typedef
            pstade::result_of<T_lambda_bind(int (*)(int), int)>::type
        b_t;

        b_t b = lambda_bind(&sum_of_args_1, 10);

        PSTADE_TEST_IS_RESULT_OF((int), b_t())

        pstade::result_of<b_t()>::type b_ = b();
        BOOST_CHECK(b_ == 10);
    }
    {
        T_plus f = lambda_unlambda(plus); // no effect
        BOOST_CHECK( f(1,2) == 3 );

        // unlambda it!
        pstade::result_of<T_lambda_unlambda(T_lambda_1)>::type u = lambda_unlambda(lambda_1);
        int i = 10;
        BOOST_CHECK( boost::lambda::bind(u, lambda_1)(i) == 10 );
    }
    {
        int i = 3;
        int (*pf)(int,int) = &my_minus;
        BOOST_CHECK( lazy(lambda_bind)(lambda_1, boost::lambda::protect(lambda_1), 10)(pf)(i) == -7 );
    }
}
