

// Boost.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/egg/shared_object.hpp>
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


void foo(boost::shared_ptr<udt> p = shared_object(1, 2))
{ }


boost::shared_ptr<udt> bar()
{
    return shared_object(1, 2);
}


void pstade_unit_test()
{
    {
        boost::shared_ptr<int> p = shared_object();
        BOOST_CHECK(*p == 0);
    }
    {
        boost::shared_ptr<udt> p = shared_object(1,2);
        BOOST_CHECK(p->m_i == 1);
        BOOST_CHECK(p->m_j == 2);
    }
    {
        ::foo();
        boost::shared_ptr<udt> p = ::bar();
    }
}
