#include <pstade/vodka/drink.hpp>


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/minimal_test.hpp>


#include <pstade/egg/identity.hpp>
#include <pstade/egg/lambda.hpp>
#include <pstade/result_of.hpp>
#include <pstade/test.hpp>


namespace egg = pstade::egg;
using namespace egg;
using pstade::result_of;


PSTADE_TEST_IS_RESULT_OF((int&), op_identity(int&))
PSTADE_TEST_IS_RESULT_OF((int const&), op_identity(int const&))
PSTADE_TEST_IS_RESULT_OF((int volatile&), op_identity(int volatile&))
PSTADE_TEST_IS_RESULT_OF((int const volatile&), op_identity(int const volatile&))
PSTADE_TEST_IS_RESULT_OF((int const&), op_identity(int))
PSTADE_TEST_IS_RESULT_OF((int const&), op_identity(int const))
PSTADE_TEST_IS_RESULT_OF((int const&), op_identity(int volatile))
PSTADE_TEST_IS_RESULT_OF((int const&), op_identity(int const volatile))


typedef result_of<op_lambda_bind(op_identity const&, op_lambda_1 const&)>::type func_t;
PSTADE_TEST_IS_RESULT_OF((int&), func_t(int&))
PSTADE_TEST_IS_RESULT_OF((int const&), func_t(int const&))
PSTADE_TEST_IS_RESULT_OF((int volatile&), func_t(int volatile&))
PSTADE_TEST_IS_RESULT_OF((int const volatile&), func_t(int const volatile&))
#if defined(PSTADE_EGG_LAMBDA_PERFECT_FUNCTORS)
    PSTADE_TEST_IS_RESULT_OF((int const&), func_t(int))
    PSTADE_TEST_IS_RESULT_OF((int const&), func_t(int const))
    PSTADE_TEST_IS_RESULT_OF((int const&), func_t(int volatile))
    PSTADE_TEST_IS_RESULT_OF((int const&), func_t(int const volatile))
#endif


void pstade_minimal_test()
{
    {
        int i = 12;
        int& i_ = identity(i);
        BOOST_CHECK( &i == &i_ );
    }
    {
        int const i = 12;
        int const& i_ = identity(i);
        BOOST_CHECK( &i == &i_ );
    }
    {
        int volatile i = 12;
        int volatile& i_ = identity(i);
        BOOST_CHECK( &i == &i_ );
    }
    {
        int const volatile i = 12;
        int const volatile& i_ = identity(i);
        BOOST_CHECK( &i == &i_ );
    }


    func_t func = lambda_bind(identity, lambda_1);
    {
        int i = 12;
        int& i_ = func(i);
        BOOST_CHECK( &i == &i_ );
    }
    {
        int const i = 12;
        int const& i_ = func(i);
        BOOST_CHECK( &i == &i_ );
    }
    {
        int volatile i = 12;
        int volatile& i_ = func(i);
        BOOST_CHECK( &i == &i_ );
    }
    {
        int const volatile i = 12;
        int const volatile& i_ = func(i);
        BOOST_CHECK( &i == &i_ );
    }
}
