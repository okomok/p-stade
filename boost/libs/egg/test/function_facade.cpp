#include <boost/egg/pstade/vodka/drink.hpp>


// Boost.Egg
//
// Copyright Shunsuke Sogame 2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/egg/function_facade.hpp>
#include <boost/egg/pstade/minimal_test.hpp>


#include <boost/type_traits/is_pod.hpp>
#include <boost/mpl/assert.hpp>
#include <boost/utility/result_of.hpp>
#include <boost/egg/pstade/unused.hpp>


struct T_foo :
    pstade::egg::function_facade<T_foo, char>
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

#define  BOOST_EGG_NULLARY_RESULT_OF_TYPE_PARAMS (T_foo)
#include BOOST_EGG_NULLARY_RESULT_OF_TYPE()


T_foo const foo = T_foo();




template< class T0, class T1 >
struct T_bar :
    pstade::egg::function_facade< T_bar<T0, T1>, char >
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

#define  BOOST_EGG_NULLARY_RESULT_OF_TEMPLATE_PARAMS (T_bar, 2) 
#include BOOST_EGG_NULLARY_RESULT_OF_TEMPLATE()


struct dummy { };

template< class T0, class T1 >
struct T_hoge
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
    typename result<T_hoge(A0, A1)>::type operator()(A0 const& a0, A1 const& a1) const
    {
        return "2";
    }

    template< class Myself, class A0 >
    struct result<Myself(A0)>
    {
        typedef int type;
    };

    template< class A0 >
    typename result<T_hoge(A0)>::type operator()(A0 const& a0) const
    {
        (void)a0;
        return 1;
    }

    char operator()() const
    {
        return '0';
    }

#if defined(BOOST_MSVC)
    T_hoge()
    { }
#endif
};

//BOOST_MPL_ASSERT_NOT(( boost::is_pod< T_hoge<int,int> > ));

namespace boost {

    template< class T0, class T1 >
    struct result_of<T_hoge<T0, T1>()>
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


struct our_identity :
    pstade::egg::function_facade<our_identity>
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

    int m_dummy1;
    int m_dummy2;
    int m_dummy3;
};


void pstade_minimal_test()
{
    {
        boost::result_of<T_foo(int, int)>::type x = foo(1, 2);
        BOOST_CHECK( x == "2" );
    }
    {
        boost::result_of<T_foo(int)>::type x = foo(1);
        BOOST_CHECK( x == 1 );
    }
    {
        boost::result_of<T_foo()>::type x = foo();
        BOOST_CHECK( x == '0' );
    }

    {
        boost::result_of<T_bar<int, int>(int, int)>::type x = foo(1, 2);
        BOOST_CHECK( x == "2" );
    }
    {
        boost::result_of<T_bar<int, int>(int)>::type x = foo(1);
        BOOST_CHECK( x == 1 );
    }
    {
        boost::result_of<T_bar<int, int>()>::type x = foo();
        BOOST_CHECK( x == '0' );
    }

    {
        boost::result_of<T_hoge<int, int>(int, int)>::type x = foo(1, 2);
        BOOST_CHECK( x == "2" );
    }
    {
        boost::result_of<T_hoge<int, int>(int)>::type x = foo(1);
        BOOST_CHECK( x == 1 );
    }
    {
        boost::result_of<T_hoge<int, int>()>::type x = foo();
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
    {
        ::our_identity id0, id1;
        BOOST_CHECK(id0(1) == 1);
        BOOST_CHECK(id1(1) == 1);
        id0 = id1;
        BOOST_CHECK(id0(1) == 1);
        BOOST_CHECK(id1(1) == 1);

        {
            ::our_identity *pid = new ::our_identity();
            ::our_identity id2 = *pid;
            delete pid;

            BOOST_ASSERT(id2.m_little.m_pfacade != pid);

            BOOST_CHECK(id2(3) == 3);
            id0 = id2;
            BOOST_CHECK(id0(3) == 3);
            BOOST_CHECK(id2(3) == 3);
        }
        {
            ::our_identity *pid = new ::our_identity();
            ::our_identity id2;
            {
                id2 = *pid;
                delete pid;
            }

            BOOST_ASSERT(id2.m_little.m_pfacade != pid);

            BOOST_CHECK(id2(3) == 3);
            id0 = id2;
            BOOST_CHECK(id0(3) == 3);
            BOOST_CHECK(id2(3) == 3);
        }
    }
}
