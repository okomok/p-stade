#include <pstade/vodka/drink.hpp>


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/minimal_test.hpp>


#include <pstade/egg/identity.hpp>
#include <pstade/egg/bll.hpp>
#include <pstade/result_of.hpp>
#include <pstade/test.hpp>


namespace egg = pstade::egg;
using namespace egg;
using pstade::result_of;

struct A
{
    A(int i) : m_i(i) {}

    operator int() const
    {
        return m_i;
    }
    
    virtual ~A() {}

    int m_i;
};


PSTADE_TEST_IS_RESULT_OF((A&), T_identity(A&))
PSTADE_TEST_IS_RESULT_OF((A const&), T_identity(A const&))
PSTADE_TEST_IS_RESULT_OF((A volatile&), T_identity(A volatile&))
PSTADE_TEST_IS_RESULT_OF((A const volatile&), T_identity(A const volatile&))
PSTADE_TEST_IS_RESULT_OF((A const&), T_identity(A))
PSTADE_TEST_IS_RESULT_OF((A const&), T_identity(A const))

#if 0 // rvalue udt seems illegal according to Comeau.
PSTADE_TEST_IS_RESULT_OF((A const&), T_identity(A volatile))
PSTADE_TEST_IS_RESULT_OF((A const&), T_identity(A const volatile))
#endif


typedef result_of<T_bll_bind(T_identity const&, T_bll_1 const&)>::type func_t;
PSTADE_TEST_IS_RESULT_OF((A&), func_t(A&))
PSTADE_TEST_IS_RESULT_OF((A const&), func_t(A const&))
PSTADE_TEST_IS_RESULT_OF((A volatile&), func_t(A volatile&))
PSTADE_TEST_IS_RESULT_OF((A const volatile&), func_t(A const volatile&))
#if defined(PSTADE_EGG_BLL_PERFECT_FUNCTORS)
    PSTADE_TEST_IS_RESULT_OF((A const&), func_t(A))
    PSTADE_TEST_IS_RESULT_OF((A const&), func_t(A const))
    PSTADE_TEST_IS_RESULT_OF((A const&), func_t(A volatile))
    PSTADE_TEST_IS_RESULT_OF((A const&), func_t(A const volatile))
#endif


void pstade_minimal_test()
{
    {
        A i = 12;
        A& i_ = identity(i);
        BOOST_CHECK( &i == &i_ );
    }
    {
        A const i = 12;
        A const& i_ = identity(i);
        BOOST_CHECK( &i == &i_ );
    }
    {
        A volatile i = 12;
        A volatile& i_ = identity(i);
        BOOST_CHECK( &i == &i_ );
    }
    {
        A const volatile i = 12;
        A const volatile& i_ = identity(i);
        BOOST_CHECK( &i == &i_ );
    }


    func_t func = bll_bind(identity, bll_1);
    {
        A i = 12;
        A& i_ = func(i);
        BOOST_CHECK( &i == &i_ );
    }
    {
        A const i = 12;
        A const& i_ = func(i);
        BOOST_CHECK( &i == &i_ );
    }
    {
        A volatile i = 12;
        A volatile& i_ = func(i);
        BOOST_CHECK( &i == &i_ );
    }
    {
        A const volatile i = 12;
        A const volatile& i_ = func(i);
        BOOST_CHECK( &i == &i_ );
    }
}
