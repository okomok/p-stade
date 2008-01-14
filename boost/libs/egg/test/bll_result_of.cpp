#include <boost/egg/pstade/vodka/drink.hpp>


// Boost.Egg
//
// Copyright Shunsuke Sogame 2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/egg/bll/result_of.hpp>
#include <boost/egg/bll/result_of.hpp>
#include <boost/egg/pstade/minimal_test.hpp>


#include <boost/egg/bll/placeholders.hpp>
#include <boost/egg/bll/bind.hpp>
#include <boost/egg/functional.hpp> // plus
#include <boost/egg/identity.hpp>
#include <boost/egg/pstade/test.hpp>


namespace bll = boost::lambda;
using namespace pstade::egg;
using pstade::result_of;


// 1ary
PSTADE_TEST_IS_RESULT_OF((int&), T_bll_1(int&))
PSTADE_TEST_IS_RESULT_OF((int const&), T_bll_1(int const&))
PSTADE_TEST_IS_RESULT_OF((int volatile&), T_bll_1(int volatile&))
PSTADE_TEST_IS_RESULT_OF((int const volatile&), T_bll_1(int const volatile&))

// Boost1.34 too can take rvalue if const-qualified one.
// Notice that function signature don't know cv-qualifier of parameters.
#if 1
    PSTADE_TEST_IS_RESULT_OF((int const&), T_bll_1(int))
    PSTADE_TEST_IS_RESULT_OF((int const&), T_bll_1(int const))
#if !BOOST_WORKAROUND(BOOST_INTEL_CXX_VERSION, BOOST_TESTED_AT(1000))
    // intel propagate cv-qualifiers. It seems a bug.
    PSTADE_TEST_IS_RESULT_OF((int const&), T_bll_1(int volatile))
    PSTADE_TEST_IS_RESULT_OF((int const&), T_bll_1(int const volatile))
#endif
#endif

// 2ary
PSTADE_TEST_IS_RESULT_OF((int&), T_bll_1(int&, double&))
PSTADE_TEST_IS_RESULT_OF((int const&), T_bll_1(int const&, double&))
#if 1
    PSTADE_TEST_IS_RESULT_OF((int const&), T_bll_1(int, double&))
    PSTADE_TEST_IS_RESULT_OF((int const&), T_bll_1(int const, double&))
#endif

// 3ary
PSTADE_TEST_IS_RESULT_OF((int&), T_bll_1(int&, double&, double&))
PSTADE_TEST_IS_RESULT_OF((int const&), T_bll_1(int const&, double&, double&))
#if 1
    PSTADE_TEST_IS_RESULT_OF((int const&), T_bll_1(int, double&, double&))
    PSTADE_TEST_IS_RESULT_OF((int const&), T_bll_1(int const, double&, double&))
#endif


// const doesn't affect.
PSTADE_TEST_IS_RESULT_OF((int&), T_bll_1 const(int&))
PSTADE_TEST_IS_RESULT_OF((int const&), T_bll_1 const(int const&))
#if 1
    PSTADE_TEST_IS_RESULT_OF((int const&), T_bll_1 const(int))
    PSTADE_TEST_IS_RESULT_OF((int const&), T_bll_1 const(int const))
#endif


struct my_two
{
    typedef int result_type;

    result_type operator()() const
    {
        return 2;
    }
};


void pstade_minimal_test()
{

    {
        int i = 10;
        result_of<T_bll_1(int&)>::type r = bll_1(i);
        BOOST_CHECK(&r == &i);
        BOOST_CHECK(r == 10);
    }
    {
        int const i = 10;
        result_of<T_bll_1(int const&)>::type r = bll_1(i);
        BOOST_CHECK(&r == &i);
        BOOST_CHECK(r == 10);
    }

#if defined(BOOST_EGG_BLL_PERFECT_FUNCTORS)
    {
        result_of<T_bll_1(int)>::type r = bll_1(10);
        BOOST_CHECK(r == 10);
    }
#endif

    {
        typedef result_of<T_bll_bind(T_plus const&, int, T_bll_1 const&)>::type fun_t;
        fun_t fun = bll_bind(plus, 3, bll_1);

        PSTADE_TEST_IS_RESULT_OF((int), fun_t(int&))
        PSTADE_TEST_IS_RESULT_OF((int), fun_t(int const&))

#if 1
        PSTADE_TEST_IS_RESULT_OF((int), fun_t(int))
        PSTADE_TEST_IS_RESULT_OF((int), fun_t(int const))
#endif

        int i = 9;
        BOOST_CHECK( fun(i) == 3+9 );
#if defined(BOOST_EGG_BLL_PERFECT_FUNCTORS)
        BOOST_CHECK( fun(9) == 3+9 );
#endif
    }

    {
        typedef result_of<T_bll_bind(T_identity const&, T_bll_1 const&)>::type fun_t;
        fun_t fun = bll_bind(identity, bll_1);

        PSTADE_TEST_IS_RESULT_OF((int&), fun_t(int&))
        PSTADE_TEST_IS_RESULT_OF((int const&), fun_t(int const&))

#if 1
        PSTADE_TEST_IS_RESULT_OF((int const&), fun_t(int))
        PSTADE_TEST_IS_RESULT_OF((int const&), fun_t(int const))
#endif

        int i = 9;
        BOOST_CHECK( fun(i) == 9 );
#if defined(BOOST_EGG_BLL_PERFECT_FUNCTORS)
        BOOST_CHECK( fun(9) == 9 );
#endif
    }

    { // nullary
        typedef result_of<T_bll_bind(my_two)>::type T_f;
        T_f f = bll_bind(my_two());
        result_of<T_f()>::type i = f();
        BOOST_CHECK(i == 2);
    }
    { // nullary
        typedef result_of<T_bll_bind const(my_two)>::type T_f;
        T_f f = bll_bind(my_two());
        result_of<T_f()>::type i = f();
        BOOST_CHECK(i == 2);
    }
}
