#include <pstade/vodka/drink.hpp>
#include <boost/test/minimal.hpp>


// PStade.Wine
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/callable_by_value.hpp>


#include <boost/mpl/assert.hpp>
#include <boost/utility/result_of.hpp>


struct op_foo :
    pstade::callable_by_value<op_foo, char>
{
    template< class Myself, class A0, class A1 = void >
    struct apply
    {
        typedef std::string type;
    };

    template< class Result, class A0, class A1 >
    Result call(A0 a0, A1 a1) const
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
    Result call(A0 a0) const
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

PSTADE_CALLABLE_NULLARY_RESULT_OF_TYPE((op_foo))

op_foo const foo = op_foo();


template< class T0, class T1 >
struct op_bar :
    pstade::callable_by_value< op_bar<T0, T1>, char >
{
    template< class Myself, class A0, class A1 = void >
    struct apply
    {
        typedef std::string type;
    };

    template< class Result, class A0, class A1 >
    Result call(A0 a0, A1 a1) const
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
    Result call(A0 a0) const
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

PSTADE_CALLABLE_NULLARY_RESULT_OF_TEMPLATE((op_bar), 2)


void test()
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
}


int test_main(int, char*[])
{
    ::test();
    return 0;
}
