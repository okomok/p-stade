#include <pstade/vodka/drink.hpp>


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/egg/auto_new.hpp>
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


PSTADE_TEST_IS_RESULT_OF((std::auto_ptr<int>), X_auto_new<int>())
PSTADE_TEST_IS_RESULT_OF((std::auto_ptr<int>), X_auto_new<int>(int))


PSTADE_TEST_IS_RESULT_OF((std::auto_ptr<udt>), X_auto_new<udt>(int,int))
PSTADE_TEST_IS_RESULT_OF((std::auto_ptr<udt const>), X_auto_new<udt const>(int,int))


void pstade_unit_test()
{
    {
        std::auto_ptr<udt> p = X_auto_new<udt>()(1,2);
        BOOST_CHECK(p->m_i == 1);
        BOOST_CHECK(p->m_j == 2);
    }
    {
        std::auto_ptr<udt> p = egg::auto_new<udt>(1,2);
        BOOST_CHECK(p->m_i == 1);
        BOOST_CHECK(p->m_j == 2);
    }
}
