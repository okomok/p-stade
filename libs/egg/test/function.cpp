#include <pstade/vodka/drink.hpp>


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/egg/function.hpp>
#include <pstade/minimal_test.hpp>


#include <string>
#include <pstade/result_of.hpp>
#include <pstade/unused.hpp>
#include <pstade/test.hpp>


#include <pstade/pod_constant.hpp>
#include <pstade/unparenthesize.hpp>

    #define PSTADE_EGG_FUNCTION(O, B) \
        typedef pstade::egg::function<PSTADE_UNPARENTHESIZE(B)> BOOST_PP_CAT(op_, O); \
        PSTADE_POD_CONSTANT((BOOST_PP_CAT(op_, O)), O) = { { } }; \
    /**/


struct baby_foo
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

PSTADE_EGG_FUNCTION(foo, (baby_foo))


PSTADE_TEST_IS_RESULT_OF((std::string), op_foo(int, double))
PSTADE_TEST_IS_RESULT_OF((int), op_foo(int))
PSTADE_TEST_IS_RESULT_OF((char), op_foo())


template< class T0, class T1 >
struct baby_bar
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
struct op_bar :
    pstade::egg::function< baby_bar<T0, T1> >
{ };

PSTADE_EGG_NULLARY_RESULT_OF_TEMPLATE(op_bar, 2)


struct baby_identity
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

typedef pstade::egg::function<baby_identity> op_identity;
op_identity const identity = { {} };


PSTADE_TEST_IS_RESULT_OF((int&), op_identity(int&))
PSTADE_TEST_IS_RESULT_OF((int const&), op_identity(int))
PSTADE_TEST_IS_RESULT_OF((int const&), op_identity(int const&))
PSTADE_TEST_IS_RESULT_OF((int const&), op_identity(int const))


void pstade_minimal_test()
{
    {
        pstade::result_of<op_foo(int, int)>::type x = foo(1, 2);
        BOOST_CHECK( x == "2" );
    }
    {
        pstade::result_of<op_foo(int)>::type x = foo(1);
        BOOST_CHECK( x == 1 );
    }
    {
        pstade::result_of<op_foo()>::type x = foo();
        BOOST_CHECK( x == '0' );
    }

    {
        pstade::result_of<op_bar<int, int>(int, int)>::type x = foo(1, 2);
        BOOST_CHECK( x == "2" );
    }
    {
        pstade::result_of<op_bar<int, int>(int)>::type x = foo(1);
        BOOST_CHECK( x == 1 );
    }
    {
        pstade::result_of<op_bar<int, int>()>::type x = foo();
        BOOST_CHECK( x == '0' );
    }
    {
        int i = 10;
        pstade::result_of<op_identity(int&)>::type x = identity(i);
        BOOST_CHECK( &x == &i );
    }
}
