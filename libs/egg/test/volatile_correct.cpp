

// Boost.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include "./egg_test.hpp"


#include <boost/egg/identity.hpp>
#include <boost/egg/bll.hpp>
#include <boost/egg/result_of.hpp>
#include "./check_is_result_of.hpp"


#include "./using_egg.hpp"
using boost::egg::result_of_;


CHECK_IS_RESULT_OF((int&), T_identity(int&))
CHECK_IS_RESULT_OF((int const&), T_identity(int const&))
CHECK_IS_RESULT_OF((int volatile&), T_identity(int volatile&))
CHECK_IS_RESULT_OF((int const volatile&), T_identity(int const volatile&))
CHECK_IS_RESULT_OF((int const&), T_identity(int))
CHECK_IS_RESULT_OF((int const&), T_identity(int const))
#if !BOOST_WORKAROUND(BOOST_INTEL_CXX_VERSION, BOOST_TESTED_AT(1000))
// intel propagate cv-qualifiers.
CHECK_IS_RESULT_OF((int const&), T_identity(int volatile))
CHECK_IS_RESULT_OF((int const&), T_identity(int const volatile))
#endif

typedef result_of_<T_bll_bind(T_identity const&, T_bll_1 const&)>::type func_t;
CHECK_IS_RESULT_OF((int&), func_t(int&))
CHECK_IS_RESULT_OF((int const&), func_t(int const&))
CHECK_IS_RESULT_OF((int volatile&), func_t(int volatile&))
CHECK_IS_RESULT_OF((int const volatile&), func_t(int const volatile&))
#if defined(BOOST_EGG_BLL_PERFECT_FUNCTORS)
    CHECK_IS_RESULT_OF((int const&), func_t(int))
    CHECK_IS_RESULT_OF((int const&), func_t(int const))
#if !BOOST_WORKAROUND(BOOST_INTEL_CXX_VERSION, BOOST_TESTED_AT(1000))
// intel propagate cv-qualifiers.
    CHECK_IS_RESULT_OF((int const&), func_t(int volatile))
    CHECK_IS_RESULT_OF((int const&), func_t(int const volatile))
#endif
#endif


void egg_test()
{
    {
        int i = 12;
        int& i_ = identity(i);
        BOOST_CHECK( &i == &i_ );
    }
    {
        int const i = 12;
        int const& i_ = identity(i);
        BOOST_CHECK( &i == &i_ );
    }
    {
        int volatile i = 12;
        int volatile& i_ = identity(i);
        BOOST_CHECK( &i == &i_ );
    }
    {
        int const volatile i = 12;
        int const volatile& i_ = identity(i);
        BOOST_CHECK( &i == &i_ );
    }


    func_t func = bll_bind(identity, bll_1);
    {
        int i = 12;
        int& i_ = func(i);
        BOOST_CHECK( &i == &i_ );
    }
    {
        int const i = 12;
        int const& i_ = func(i);
        BOOST_CHECK( &i == &i_ );
    }
    {
        int volatile i = 12;
        int volatile& i_ = func(i);
        BOOST_CHECK( &i == &i_ );
    }
    {
        int const volatile i = 12;
        int const volatile& i_ = func(i);
        BOOST_CHECK( &i == &i_ );
    }
}
