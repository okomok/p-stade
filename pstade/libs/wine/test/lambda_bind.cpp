#include <pstade/vodka/drink.hpp>
#include <boost/test/minimal.hpp>


// PStade.Wine
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/lambda_bind.hpp>


#include <pstade/lambda_placeholders.hpp>
#include <boost/utility/result_of.hpp>
#include <pstade/functional.hpp>
#include <pstade/reference.hpp>


using namespace pstade;


void test()
{
    {
        boost::result_of<op_lambda_bind(op_plus, op_lambda_1, int)>::type b =
            lambda_bind(plus, lambda_1, 10);

        BOOST_CHECK( b(20|to_reference) == 30 );
    }
}


int test_main(int, char*[])
{
    ::test();
    return 0;
}
