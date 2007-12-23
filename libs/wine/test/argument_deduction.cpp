#include <pstade/vodka/drink.hpp>


// PStade.Wine
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/lightweight_test.hpp>


#include <boost/type.hpp>
#include <boost/mpl/assert.hpp>
#include <boost/type_traits/is_same.hpp>
#include <pstade/boost_workaround.hpp>


// Conclusion (for now):
//
//    A volatile object can't be rvalue.
//


bool g_const_called;

template<class T, class D>
void foo(T& x, boost::type<D>)
{
    BOOST_MPL_ASSERT((boost::is_same<T, D>));
    g_const_called = false;
}

template<class T, class D>
void foo(T const &x, boost::type<D>)
{
    BOOST_MPL_ASSERT((boost::is_same<T, D>));
    g_const_called = true;
}


int make_int() { return 3; }
int const make_int_c() { return 3; } // cv-qualifed ignored
int volatile make_int_v() { return 3; } // cv-qualifed ignored
int const volatile make_int_cv() { return 3; } // cv-qualifed ignored


struct udt { };
udt make_udt() { return udt(); }
udt const make_udt_c() { return udt(); }
udt volatile make_udt_v() { return udt(); }
udt const volatile make_udt_cv() { return udt(); }


void test_builtin()
{
    // lvalue
    {
        int x = 0;
        ::foo(x, boost::type<int>());
        BOOST_CHECK(!g_const_called);
    }
    {
        int const x = 0;
        ::foo(x, boost::type<int>());
        BOOST_CHECK(g_const_called);
    }
    {
        int volatile x = 0;
        ::foo(x, boost::type<int volatile>());
        BOOST_CHECK(!g_const_called);
    }
    {
        int const volatile x = 0;
        ::foo(x, boost::type<int volatile>());
        BOOST_CHECK(g_const_called);
    }

    // rvalue
    {
        ::foo(10, boost::type<int>());
        BOOST_CHECK(g_const_called);
    }
    {
        ::foo((int const)10, boost::type<int>());
        BOOST_CHECK(g_const_called);
    }
    {
#if !BOOST_WORKAROUND(__GNUC__, == 3) // seems bug of gcc3
        ::foo((int volatile)10, boost::type<int>());
        BOOST_CHECK(g_const_called);
#endif
    }
    {
#if !BOOST_WORKAROUND(__GNUC__, == 3) // seems bug of gcc3
        ::foo((int const volatile)10, boost::type<int>());
        BOOST_CHECK(g_const_called);
#endif
    }
    {
        ::foo(::make_int(), boost::type<int>());
        BOOST_CHECK(g_const_called);
    }
    {
        ::foo(::make_int_c(), boost::type<int>());
        BOOST_CHECK(g_const_called);
    }
    {
#if 0
    // Hmm, no conclusion around compilers: gcc, msvc, and intel.
    // Comean and I agree this should compile and run.
        ::foo(::make_int_cv(), boost::type<int>());
        BOOST_CHECK(g_const_called);
#endif
    }
}


void test_udt()
{
    // lvalue
    {
        udt x = {};
        ::foo(x, boost::type<udt>());
        BOOST_CHECK(!g_const_called);
    }
    {
        udt const x = {};
        ::foo(x, boost::type<udt>());
        BOOST_CHECK(g_const_called);
    }
    {
        udt volatile x = {};
        ::foo(x, boost::type<udt volatile>());
        BOOST_CHECK(!g_const_called);
    }
    {
        udt const volatile x = {};
        ::foo(x, boost::type<udt volatile>());
        BOOST_CHECK(g_const_called);
    }

    // rvalue
    {
        ::foo(make_udt(), boost::type<udt>());
        BOOST_CHECK(g_const_called);
    }
    {
        ::foo((udt const)make_udt(), boost::type<udt>());
        BOOST_CHECK(g_const_called);
    }
    {
#if 0 // Comeau says: error: initial value of reference to const volatile must be an lvalue
        ::foo((udt volatile)make_udt(), boost::type<udt>());
        BOOST_CHECK(g_const_called);
#endif
    }
    {
#if 0 // Comeau says: error: initial value of reference to const volatile must be an lvalue
        ::foo((udt const volatile)make_udt(), boost::type<udt>());
        BOOST_CHECK(g_const_called);
#endif
    }

    {
        ::foo(::make_udt(), boost::type<udt>());
        BOOST_CHECK(g_const_called);
    }
    {
        ::foo(::make_udt_c(), boost::type<udt>());
        BOOST_CHECK(g_const_called);
    }
#if 0 // Comeau says: error: initial value of reference to const volatile must be an lvalue
    {
        ::foo(::make_udt_cv(), boost::type<udt>());
        BOOST_CHECK(g_const_called);
    }
#endif
}



void pstade_lightweight_test()
{
    test_builtin();
    test_udt();
}
