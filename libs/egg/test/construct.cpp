

// Boost.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/egg/construct.hpp>
#include "./egg_unit_test.hpp"


#include <pstade/test.hpp>


#include "./using_egg.hpp"


struct udt
{
    udt(int i, int j)
        : m_i(i), m_j(j)
    { }

    int m_i, m_j;
};


PSTADE_TEST_IS_RESULT_OF((int), X_construct<int>())
PSTADE_TEST_IS_RESULT_OF((int), X_construct<int>(int))


PSTADE_TEST_IS_RESULT_OF((udt), X_construct<udt>(int,int))
PSTADE_TEST_IS_RESULT_OF((udt) const, X_construct<udt const>(int,int))


void egg_unit_test()
{
    {
        udt x = X_construct<udt>()(1,2);
        BOOST_CHECK(x.m_i == 1);
        BOOST_CHECK(x.m_j == 2);
    }
}
