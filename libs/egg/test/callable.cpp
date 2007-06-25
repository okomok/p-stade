#include <pstade/vodka/drink.hpp>
#include <boost/test/minimal.hpp>


// PStade.Wine
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/egg/callable.hpp>
#include <pstade/egg/nullary_result_of.hpp>
#include <pstade/minimal_test.hpp>


#include <string>
#include <boost/utility/result_of.hpp>
#include <pstade/unused.hpp>
#include <pstade/test.hpp>


struct op_foo :
    pstade::egg::callable<op_foo, char>
{
    template< class Myself, class A0, class A1 = void >
    struct apply
    {
        typedef std::string type;
    };

    template< class Result, class A0, class A1 >
    Result call(A0& a0, A1& a1, boost::type<Result>) const
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
    Result call(A0& a0, boost::type<Result>) const
    {
        (void)a0;
        return 1;
    }

    template< class Result >
    Result call(boost::type<Result>) const
    {
        return '0';
    }
};

PSTADE_EGG_NULLARY_RESULT_OF_TYPE(op_foo)

PSTADE_TEST_IS_RESULT_OF((std::string), op_foo(int, double))
PSTADE_TEST_IS_RESULT_OF((int), op_foo(int))
PSTADE_TEST_IS_RESULT_OF((char), op_foo())


op_foo const foo = op_foo();




template< class T0, class T1 >
struct op_bar :
    pstade::egg::callable< op_bar<T0, T1>, char >
{
    template< class Myself, class A0, class A1 = void >
    struct apply
    {
        typedef std::string type;
    };

    template< class Result, class A0, class A1 >
    Result call(A0& a0, A1& a1, boost::type<Result>) const
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
    Result call(A0& a0, boost::type<Result>) const
    {
        (void)a0;
        return 1;
    }

    template< class Result >
    Result call(boost::type<Result>) const
    {
        return '0';
    }
};

PSTADE_EGG_NULLARY_RESULT_OF_TEMPLATE(op_bar, 2)


struct my_identity :
    pstade::egg::callable<my_identity>
{
    template< class Myself, class A0 >
    struct apply
    {
        typedef A0& type;
    };

    template< class Result, class A0 >
    Result call(A0& a0, boost::type<Result>) const
    {
        return a0;
    }
};


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
        boost::result_of<my_identity(int&)>::type x = my_identity()(i);
        BOOST_CHECK( &x == &i );
    }
}
