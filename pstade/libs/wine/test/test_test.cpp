#include <pstade/vodka/drink.hpp>


// PStade.Wine
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/test.hpp>
#include <boost/test/minimal.hpp>


struct T_my_fun
{
    template<class Sig>
    struct result;

    template<class Self, class A0>
    struct result<Self(A0)>
    {
        typedef A0 type;
    };
};
PSTADE_TEST_IS_RESULT_OF((int), T_my_fun(int))
PSTADE_TEST_IS_RESULT_OF((int), T_my_fun(int const)) // because of a signature rule.
PSTADE_TEST_IS_RESULT_OF((int&), T_my_fun(int&))
PSTADE_TEST_IS_RESULT_OF((int const&), T_my_fun(int const&))


// keep const check
struct T_my_const_fun
{
    template<class Sig>
    struct result;

    template<class Self, class A0>
    struct result<Self(A0)>
    {
        typedef A0 const type;
    };
};
PSTADE_TEST_IS_RESULT_OF((int) const, T_my_const_fun(int))
PSTADE_TEST_IS_RESULT_OF((int) const, T_my_const_fun(int const))


PSTADE_TEST_IS_SAME((int) const, (int) const)
PSTADE_TEST_IS_SAME((int), (int))
PSTADE_TEST_IS_SAME((int&), (int&))
PSTADE_TEST_IS_SAME((int const&), (int const&))


int test_main(int, char*[])
{
    return 0;
}
