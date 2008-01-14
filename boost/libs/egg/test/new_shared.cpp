#include <boost/egg/pstade/vodka/drink.hpp>


// Boost.Egg
//
// Copyright Shunsuke Sogame 2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/egg/new_shared.hpp>
#include <boost/egg/pstade/unit_test.hpp>


#include <boost/egg/pstade/test.hpp>


namespace egg = pstade::egg;
using namespace egg;


struct udt
{
    udt(int i, int j)
        : m_i(i), m_j(j)
    { }

    int m_i, m_j;
};


PSTADE_TEST_IS_RESULT_OF((boost::shared_ptr<int>), X_new_shared<int>())
PSTADE_TEST_IS_RESULT_OF((boost::shared_ptr<int>), X_new_shared<int>(int))


PSTADE_TEST_IS_RESULT_OF((boost::shared_ptr<udt>), X_new_shared<udt>(int,int))
PSTADE_TEST_IS_RESULT_OF((boost::shared_ptr<udt const>), X_new_shared<udt const>(int,int))


void pstade_unit_test()
{
    {
        boost::shared_ptr<udt> p = X_new_shared<udt>()(1,2);
        BOOST_CHECK(p->m_i == 1);
        BOOST_CHECK(p->m_j == 2);
    }
}
