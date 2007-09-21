#include <pstade/vodka/drink.hpp>


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/egg/reset.hpp>
#include <pstade/minimal_test.hpp>


#include <pstade/test.hpp>
#include <boost/shared_ptr.hpp>
#include <memory> // auto_ptr


namespace egg = pstade::egg;
using namespace egg;


PSTADE_TEST_IS_RESULT_OF((void), op_reset(int&, int &))
PSTADE_TEST_IS_RESULT_OF((void), op_reset(int&, int, int, int))


struct Pair
{
    Pair(int i, int j) : m_i(i), m_j(j) { }

    int m_i, m_j;
};


void pstade_minimal_test()
{
    {
        boost::shared_ptr<int> p;
        reset(p, new int (4));
        BOOST_CHECK( *p == 4 );
        reset(p);
        BOOST_CHECK( !p );
    }

    {
        boost::shared_ptr<int> p;
        std::auto_ptr<int> l(new int(4));
        reset(p, l);
        BOOST_CHECK( *p == 4 );
        reset(p);
        BOOST_CHECK( !p );
    }

    {
        boost::shared_ptr<int> p;
        move_reset(p, std::auto_ptr<int>(new int(4)));
        BOOST_CHECK( *p == 4 );
        reset(p);
        BOOST_CHECK( !p );
    }
    {
        Pair pa(3, 4);
        reset(pa, 1, 2);
        BOOST_CHECK(pa.m_i == 1);
        BOOST_CHECK(pa.m_j == 2);
    }
}
