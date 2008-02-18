

// Boost.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/egg/shared_new.hpp>
#include <pstade/unit_test.hpp>


#include <pstade/test.hpp>


#include "./using_egg.hpp"


struct udt
{
    udt(int i, int j)
        : m_i(i), m_j(j)
    { }

    int m_i, m_j;
};


PSTADE_TEST_IS_RESULT_OF((boost::shared_ptr<int>), X_shared_new<int>())
PSTADE_TEST_IS_RESULT_OF((boost::shared_ptr<int>), X_shared_new<int>(int))


PSTADE_TEST_IS_RESULT_OF((boost::shared_ptr<udt>), X_shared_new<udt>(int,int))
PSTADE_TEST_IS_RESULT_OF((boost::shared_ptr<udt const>), X_shared_new<udt const>(int,int))


void pstade_unit_test()
{
    {
        boost::shared_ptr<udt> p = X_shared_new<udt>()(1,2);
        BOOST_CHECK(p->m_i == 1);
        BOOST_CHECK(p->m_j == 2);
    }
    {
        boost::shared_ptr<udt> p = egg::shared_new<udt>(1,2);
        BOOST_CHECK(p->m_i == 1);
        BOOST_CHECK(p->m_j == 2);
    }
}
