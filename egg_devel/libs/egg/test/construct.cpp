

// Boost.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/egg/construct.hpp>
#include "./egg_test.hpp"


#include "./check_is_result_of.hpp"


#include "./using_egg.hpp"


struct udt
{
    udt(int i, int j)
        : m_i(i), m_j(j)
    { }

    int m_i, m_j;
};


CHECK_IS_RESULT_OF(int, X_construct<int>())
CHECK_IS_RESULT_OF(int, X_construct<int>(int))


CHECK_IS_RESULT_OF(udt, X_construct<udt>(int,int))
CHECK_IS_RESULT_OF(udt const, X_construct<udt const>(int,int))


void egg_test()
{
    {
        udt x = X_construct<udt>()(1,2);
        BOOST_CHECK(x.m_i == 1);
        BOOST_CHECK(x.m_j == 2);
    }
}
