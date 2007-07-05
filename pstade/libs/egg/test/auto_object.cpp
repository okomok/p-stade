#include <pstade/vodka/drink.hpp>


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/egg/auto_object.hpp>
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


void foo(std::auto_ptr<udt> p = auto_object(1, 2))
{ }


std::auto_ptr<udt> bar()
{
    // msvc-7.1 warns but compiles.
    return auto_object(1, 2);
}


void pstade_unit_test()
{
    {
        std::auto_ptr<int> p = auto_object();
        BOOST_CHECK(*p == 0);
    }
    {
        std::auto_ptr<udt> p = auto_object(1,2);
        BOOST_CHECK(p->m_i == 1);
        BOOST_CHECK(p->m_j == 2);
    }
    {
        ::foo();
        std::auto_ptr<udt> p = ::bar();
    }
}
