#include <pstade/vodka/drink.hpp>


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/egg/construct.hpp>
#include <pstade/unit_test.hpp>


#include <pstade/test.hpp>


namespace egg = pstade::egg;
using namespace egg;


struct udt
{
    udt(int i, int j)
        : m_i(i), m_j(j)
    { }

    int m_i, m_j;
};


PSTADE_TEST_IS_RESULT_OF((int), xp_construct<int>())
PSTADE_TEST_IS_RESULT_OF((int), xp_construct<int>(int))


PSTADE_TEST_IS_RESULT_OF((udt), xp_construct<udt>(int,int))
PSTADE_TEST_IS_RESULT_OF((udt const), xp_construct<udt const>(int,int))


void pstade_unit_test()
{
    {
        udt x = xp_construct<udt>()(1,2);
        BOOST_CHECK(x.m_i == 1);
        BOOST_CHECK(x.m_j == 2);
    }
}
