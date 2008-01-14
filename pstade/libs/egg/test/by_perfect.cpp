#include <pstade/vodka/drink.hpp>


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/egg/by_perfect.hpp>
#include <pstade/minimal_test.hpp>


#include <string>
#include <pstade/result_of.hpp>
#include <pstade/unused.hpp>
#include <pstade/test.hpp>

#include <boost/lambda/bind.hpp>
#include <boost/lambda/core.hpp>
#include <boost/lambda/lambda.hpp>


#include <pstade/pod_constant.hpp>
#include <pstade/unparenthesize.hpp>

    #define PSTADE_EGG_FUNCTION_DEF(O, B) \
        typedef pstade::egg::function<PSTADE_UNPARENTHESIZE(B), pstade::egg::by_perfect> BOOST_PP_CAT(T_, O); \
        PSTADE_POD_CONSTANT((BOOST_PP_CAT(T_, O)), O) = { { } }; \
    /**/


struct little_foo
{
    template<class Myself, class A0, class A1 = void>
    struct apply
    {
        typedef std::string type;
    };

    template<class Result, class A0, class A1>
    Result call(A0& a0, A1& a1) const
    {
        (void)a0; (void)a1;
        return "2";
    }

    template<class Myself, class A0>
    struct apply<Myself, A0>
    {
        typedef int type;
    };

    template<class Result, class A0>
    Result call(A0& a0) const
    {
        (void)a0;
        return 1;
    }

    typedef char nullary_result_type;

    template< class Result >
    Result call() const
    {
        return '0';
    }
};

PSTADE_EGG_FUNCTION_DEF(foo, (little_foo))


PSTADE_TEST_IS_RESULT_OF((std::string), T_foo(int, double))
PSTADE_TEST_IS_RESULT_OF((int), T_foo(int))
PSTADE_TEST_IS_RESULT_OF((char), T_foo())


template< class T0, class T1 >
struct little_bar
{
    template< class Myself, class A0, class A1 = void >
    struct apply
    {
        typedef std::string type;
    };

    template< class Result, class A0, class A1 >
    Result call(A0& a0, A1& a1) const
    {
        (void)a0; (void)a1;
        return "2";
    }

    template< class Myself, class A0 >
    struct apply<Myself, A0>
    {
        typedef int type;
    };

    template< class Result, class A0 >
    Result call(A0& a0) const
    {
        (void)a0;
        return 1;
    }

    typedef char nullary_result_type;

    template< class Result >
    Result call() const
    {
        return '0';
    }
};

template<class T0, class T1>
struct T_bar :
    pstade::egg::function< little_bar<T0, T1>, pstade::egg::by_perfect >
{ };


#define  PSTADE_EGG_NULLARY_RESULT_OF_TEMPLATE_PARAMS (T_bar, 2)
#include PSTADE_EGG_NULLARY_RESULT_OF_TEMPLATE()


struct little_identity
{
    template< class Myself, class A0 >
    struct apply
    {
        typedef A0& type;
    };

    template< class Result, class A0 >
    Result call(A0& a0) const
    {
        return a0;
    }
};

typedef pstade::egg::function<little_identity, pstade::egg::by_perfect> T_identity;
T_identity const identity = { {} };


PSTADE_TEST_IS_RESULT_OF((int&), T_identity(int&))
PSTADE_TEST_IS_RESULT_OF((int const&), T_identity(int))
PSTADE_TEST_IS_RESULT_OF((int const&), T_identity(int const&))
PSTADE_TEST_IS_RESULT_OF((int const&), T_identity(int const))


struct little_keep_const
{
    template< class Myself, class A0 >
    struct apply
    {
        typedef A0 type;
    };

    template< class Result, class A0 >
    Result call(A0& a0) const
    {
        return a0;
    }
};
typedef pstade::egg::function<little_keep_const, pstade::egg::by_perfect> T_keep_const;
T_keep_const const keep_const = { {} };
BOOST_MPL_ASSERT((boost::is_same< pstade::egg::detail::unref<pstade::egg::by_perfect, int&>::type, int >));
BOOST_MPL_ASSERT((boost::is_same< pstade::egg::detail::unref<pstade::egg::by_perfect, int const&>::type, int const >));
BOOST_MPL_ASSERT((boost::is_same< pstade::egg::detail::unref<pstade::egg::by_perfect, int>::type, int const >));
BOOST_MPL_ASSERT((boost::is_same< pstade::egg::detail::unref<pstade::egg::by_perfect, int const>::type, int const >));
PSTADE_TEST_IS_RESULT_OF((int), T_keep_const(int&))
PSTADE_TEST_IS_RESULT_OF((int) const, T_keep_const(int))
PSTADE_TEST_IS_RESULT_OF((int) const, T_keep_const(int const&))
PSTADE_TEST_IS_RESULT_OF((int) const, T_keep_const(int const))



void pstade_minimal_test()
{
    {
        pstade::result_of<T_foo(int, int)>::type x = foo(1, 2);
        BOOST_CHECK( x == "2" );

        int i = 5;
        BOOST_CHECK( boost::lambda::bind(foo, 3, boost::lambda::_1)(i) == "2" );
        BOOST_CHECK( boost::lambda::bind(foo, 3, 2)() == "2" );
    }
    {
        pstade::result_of<T_foo(int)>::type x = foo(1);
        BOOST_CHECK( x == 1 );

        int i = 5;
        BOOST_CHECK( boost::lambda::bind(foo, 3)() == 1 );
        BOOST_CHECK( boost::lambda::bind(foo, boost::lambda::_1)(i) == 1 );
    }
    {
        pstade::result_of<T_foo()>::type x = foo();
        BOOST_CHECK( x == '0' );

        BOOST_CHECK( boost::lambda::bind(foo)() == '0' );
    }

    {
        pstade::result_of<T_bar<int, int>(int, int)>::type x = foo(1, 2);
        BOOST_CHECK( x == "2" );
    }
    {
        pstade::result_of<T_bar<int, int>(int)>::type x = foo(1);
        BOOST_CHECK( x == 1 );
    }
    {
        pstade::result_of<T_bar<int, int>()>::type x = foo();
        BOOST_CHECK( x == '0' );
    }
    {
        int i = 10;
        pstade::result_of<T_identity(int&)>::type x = identity(i);
        BOOST_CHECK( &x == &i );
    }
    {
        pstade::result_of<T_keep_const(int)>::type x = keep_const(3);
        (void)x;
    }
}
