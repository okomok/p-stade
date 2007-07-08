#include <pstade/vodka/drink.hpp>


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/egg/function_facade.hpp>
#include <pstade/minimal_test.hpp>


#include <boost/type_traits/is_pod.hpp>
#include <boost/mpl/assert.hpp>
#include <boost/utility/result_of.hpp>
#include <pstade/unused.hpp>


struct op_foo :
    pstade::egg::function_facade<op_foo, char>
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

PSTADE_EGG_NULLARY_RESULT_OF_TYPE(op_foo)


op_foo const foo = op_foo();




template< class T0, class T1 >
struct op_bar :
    pstade::egg::function_facade< op_bar<T0, T1>, char >
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

PSTADE_EGG_NULLARY_RESULT_OF_TEMPLATE(op_bar, 2)


struct dummy { };

template< class T0, class T1 >
struct op_hoge
    // :dummy // also can work around!
{
    template< class Signature >
    struct result;

    template< class Myself, class A0, class A1 >
    struct result<Myself(A0, A1)>
    {
        typedef std::string type;
    };

    template< class A0, class A1 >
    typename result<op_hoge(A0, A1)>::type operator()(A0 const& a0, A1 const& a1) const
    {
        return "2";
    }

    template< class Myself, class A0 >
    struct result<Myself(A0)>
    {
        typedef int type;
    };

    template< class A0 >
    typename result<op_hoge(A0)>::type operator()(A0 const& a0) const
    {
        (void)a0;
        return 1;
    }

    char operator()() const
    {
        return '0';
    }

#if defined(BOOST_MSVC)
    op_hoge()
    { }
#endif
};

//BOOST_MPL_ASSERT_NOT(( boost::is_pod< op_hoge<int,int> > ));

namespace boost {

    template< class T0, class T1 >
    struct result_of<op_hoge<T0, T1>()>
    {
        typedef char type;
    };

}


struct error_msg_check :
    pstade::egg::function_facade<error_msg_check>
{
    template< class Myself, class A0 >
    struct apply
    {
        typedef int type;
    };

    template< class Result, class A0 >
    Result call(A0& a0) const
    {
        return 1;
    }
};


struct my_identity :
    pstade::egg::function_facade<my_identity>
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

struct A { A() { } A(A const volatile&) { } };

A volatile get_volatile()
{
    A volatile a;
    return a;
}

A const volatile get_cv()
{
    A const volatile a;
    return a;
}


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
        boost::result_of<op_hoge<int, int>(int, int)>::type x = foo(1, 2);
        BOOST_CHECK( x == "2" );
    }
    {
        boost::result_of<op_hoge<int, int>(int)>::type x = foo(1);
        BOOST_CHECK( x == 1 );
    }
    {
        boost::result_of<op_hoge<int, int>()>::type x = foo();
        BOOST_CHECK( x == '0' );
    }

#if 0
    {
        error_msg_check()();
    }
#endif

    {
        int volatile x = 0;
        int volatile &x_ = ::my_identity()(x);
        pstade::unused(x, x_);
    }
    {
        int const volatile x = 0;
        int const volatile &x_ = ::my_identity()(x);
        pstade::unused(x, x_);
    }
#if !defined(__GNUC__)
    {
        ::A const volatile &x_ = ::my_identity()(::get_volatile());
        pstade::unused(x_);
    }
    {
        ::A const volatile &x_ = ::my_identity()(::get_cv());
        pstade::unused(x_);
    }
#endif
}
