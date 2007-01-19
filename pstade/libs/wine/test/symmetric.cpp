#include <pstade/vodka/drink.hpp>
#include <boost/test/minimal.hpp>


// PStade.Wine
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/symmetric.hpp>


#include <pstade/test.hpp>


struct our_fun_t
{
    typedef int result_type;

    int operator()(int x) const
    {
        return x + 1;
    }
};

PSTADE_SYMMETRIC(our_fun, (our_fun_t))


PSTADE_TEST_IS_RESULT_OF((int), op_our_fun(int))


void test()
{
    BOOST_CHECK( our_fun(3) == 4 );
    BOOST_CHECK( (3|our_fun) == 4 );
    BOOST_CHECK( (3|our_fun()) == 4 );
}


int test_main(int, char*[])
{
    ::test();
    return 0;
}
