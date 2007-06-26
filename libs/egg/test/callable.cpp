#include <pstade/vodka/drink.hpp>


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/egg/callable.hpp>
#include <pstade/minimal_test.hpp>


#include <pstade/pod_constant.hpp>
#include <string>
#include <boost/utility/result_of.hpp>
#include <pstade/unused.hpp>
#include <pstade/test.hpp>


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

    template< class Result >
    Result call() const
    {
        return '0';
    }
};

typedef pstade::egg::callable<baby_foo, char> op_foo;
PSTADE_POD_CONSTANT(foo, (op_foo))


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

    template< class Result >
    Result call() const
    {
        return '0';
    }
};

template<class T0, class T1>
struct op_bar :
    pstade::egg::callable< baby_bar<T0, T1>, char >
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

typedef pstade::egg::callable<baby_identity> op_identity;
PSTADE_POD_CONSTANT(identity, (op_identity))


PSTADE_TEST_IS_RESULT_OF((int&), op_identity(int&))
PSTADE_TEST_IS_RESULT_OF((int const&), op_identity(int))
PSTADE_TEST_IS_RESULT_OF((int const&), op_identity(int const&))
PSTADE_TEST_IS_RESULT_OF((int const&), op_identity(int const))


void pstade_minimal_test()
{
    {
        boost::result_of<op_foo(int, int)>::type x = foo(1, 2);
        BOOST_CHECK( x == "2" );
    }
    {
        boost::result_of<op_foo(int)>::type x = foo(1);
        BOOST_CHECK( x == 1 );
    }
    {
        boost::result_of<op_foo()>::type x = foo();
        BOOST_CHECK( x == '0' );
    }

    {
        boost::result_of<op_bar<int, int>(int, int)>::type x = foo(1, 2);
        BOOST_CHECK( x == "2" );
    }
    {
        boost::result_of<op_bar<int, int>(int)>::type x = foo(1);
        BOOST_CHECK( x == 1 );
    }
    {
        boost::result_of<op_bar<int, int>()>::type x = foo();
        BOOST_CHECK( x == '0' );
    }
    {
        int i = 10;
        boost::result_of<op_identity(int&)>::type x = identity(i);
        BOOST_CHECK( &x == &i );
    }
}
