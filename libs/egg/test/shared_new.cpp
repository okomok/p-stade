

// Boost.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/egg/shared_new.hpp>
#include "./egg_unit_test.hpp"


#include "./check_is_result_of.hpp"


#include "./using_egg.hpp"


struct udt
{
    udt(int i, int j)
        : m_i(i), m_j(j)
    { }

    int m_i, m_j;
};


CHECK_IS_RESULT_OF(boost::shared_ptr<int>, X_shared_new<int>())
CHECK_IS_RESULT_OF(boost::shared_ptr<int>, X_shared_new<int>(int))


CHECK_IS_RESULT_OF(boost::shared_ptr<udt>, X_shared_new<udt>(int,int))
CHECK_IS_RESULT_OF(boost::shared_ptr<udt const>, X_shared_new<udt const>(int,int))


void egg_unit_test()
{
    {
        boost::shared_ptr<udt> p = X_shared_new<udt>()(1,2);
        BOOST_CHECK(p->m_i == 1);
        BOOST_CHECK(p->m_j == 2);
    }
#if 0 // rejected
    {
        boost::shared_ptr<udt> p = egg::shared_new<udt>(1,2);
        BOOST_CHECK(p->m_i == 1);
        BOOST_CHECK(p->m_j == 2);
    }
#endif
}
