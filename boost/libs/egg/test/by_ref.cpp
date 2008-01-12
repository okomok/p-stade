#include <boost/egg/pstade/vodka/drink.hpp>


// Boost.Egg
//
// Copyright Shunsuke Sogame 2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/egg/by_ref.hpp>
#include <boost/egg/pstade/minimal_test.hpp>


#include <string>
#include <memory> // auto_ptr
#include <boost/egg/pstade/result_of.hpp>
#include <boost/egg/pstade/unused.hpp>
#include <boost/egg/pstade/test.hpp>


#include <boost/egg/pstade/pod_constant.hpp>
#include <boost/egg/pstade/unparenthesize.hpp>

    #define BOOST_EGG_FUNCTION_BY_REF(O, B) \
        typedef pstade::egg::function<PSTADE_UNPARENTHESIZE(B), pstade::egg::by_ref> BOOST_PP_CAT(T_, O); \
        PSTADE_POD_CONSTANT((BOOST_PP_CAT(T_, O)), O) = { { } }; \
    /**/


struct little_foo
{
    template< class Myself, class A0, class A1 = void >
    struct apply
    {
        typedef A0 type;
    };

    template< class Result, class A0, class A1 >
    Result call(A0& a0, A1 const& a1) const
    {
        return a0 + a1;
    }

    template< class Myself, class A0 >
    struct apply<Myself, A0>
    {
        typedef A0& type;
    };

    template< class Result, class A0 >
    Result call(A0& a0) const
    {
        return a0;
    }

    typedef char nullary_result_type;

    template< class Result >
    Result call() const
    {
        return '0';
    }
};

BOOST_EGG_FUNCTION_BY_REF(foo, (little_foo))

PSTADE_TEST_IS_RESULT_OF((int), T_foo(int&, int&))
PSTADE_TEST_IS_RESULT_OF((int) const, T_foo(int const&, int&))
PSTADE_TEST_IS_RESULT_OF((int&), T_foo(int&))
PSTADE_TEST_IS_RESULT_OF((int const&), T_foo(int const&))
PSTADE_TEST_IS_RESULT_OF((char), T_foo())


struct little_big_arity
{
    template<class Myself, class A0, class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9>
    struct apply
    {
        typedef A0& type;
    };

    template<class Result, class A0>
    Result call(A0& a0, ...) const
    {
        return a0;
    }
};

BOOST_EGG_FUNCTION_BY_REF(big_arity, (little_big_arity))



void pstade_minimal_test()
{
    {
        int i = 1, j = 2;
        pstade::result_of<T_foo(int&, int&)>::type x = foo(i, j);
        BOOST_CHECK( x == 3 );
    }
    {
        int i = 1;
        pstade::result_of<T_foo(int&)>::type x = foo(i);
        BOOST_CHECK( &i == &x );
    }
    {
        pstade::result_of<T_foo()>::type x = foo();
        BOOST_CHECK( x == '0' );
    }
    {
        int const i0 = 1, i1 = 1, i2 = 2, i3 = 3, i4 = 4;
        int i5 = 5, i6 = 6, i7 = 7, i8 = 8, i9 = 9;
        BOOST_CHECK( &(big_arity(i0,i1,i2,i3,i4,i5,i6,i7,i8,i9)) == &i0 );
    }
}
