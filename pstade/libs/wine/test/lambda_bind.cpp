#include <pstade/vodka/drink.hpp>
#include <boost/test/minimal.hpp>


// PStade.Wine
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/lambda_bind.hpp>
#include <pstade/lambda_result_of.hpp>


#include <boost/utility/result_of.hpp>
#include <pstade/functional.hpp>
#include <pstade/as.hpp>
#include <pstade/test.hpp>


using namespace pstade;


int sum_of_args_1(int a) { return a; }

void test()
{
    {
        boost::result_of<op_lambda_bind(op_plus, op_lambda_1, int)>::type b =
            lambda_bind(plus, lambda_1, 10);

        BOOST_CHECK( b(20|as_ref) == 30 );
    }
    {
        typedef
            boost::result_of<op_lambda_bind(int (*)(int), int)>::type
        b_t;

        b_t b = lambda_bind(&sum_of_args_1, 10);

        PSTADE_TEST_IS_RESULT_OF((int), b_t())

        boost::result_of<b_t()>::type b_ = b();
        BOOST_CHECK(b_ == 10);
    }
}


int test_main(int, char*[])
{
    ::test();
    return 0;
}
