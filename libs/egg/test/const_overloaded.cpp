

// Boost.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/egg/detail/const_overloaded.hpp>
#include "./egg_test.hpp"


template<class E, class A>
void algo1(A& a BOOST_EGG_CONST_OVERLOADED(A))
{
    (void)a;
}

template<class E, class A>
void algo1(A const& a)
{
    (void)a;
}


// Can be added to both.
// But if BOOST_EGG_CONST_OVERLOADED is turned on,
// VC++ would be broken when 'A' is deduced as an array type.
template<class E, class A>
void algo1_(A& a BOOST_EGG_CONST_OVERLOADED(A))
{
    (void)a;
}

template<class E, class A>
void algo1_(A const& a BOOST_EGG_CONST_OVERLOADED(A))
{
    (void)a;
}


// forwarding
template<class E, class A0, class A1>
void algo2(A0& a0, A1& a1 BOOST_EGG_CONST_OVERLOADED_PARAMS(2, A))
{
    (void)a0; (void)a1;
}

template<class E, class A0, class A1>
void algo2(A0& a0, A1 const& a1 BOOST_EGG_CONST_OVERLOADED_PARAMS(2, A))
{
    (void)a0; (void)a1;
}

template<class E, class A0, class A1>
void algo2(A0 const& a0, A1& a1 BOOST_EGG_CONST_OVERLOADED_PARAMS(2, A))
{
    (void)a0; (void)a1;
}

template<class E, class A0, class A1>
void algo2(A0 const& a0, A1 const& a1 BOOST_EGG_CONST_OVERLOADED_PARAMS(2, A))
{
    (void)a0; (void)a1;
}


void egg_test()
{
    {
        int a = 0;
        int const ca = 0;

        ::algo1<char>(a);
        ::algo1<char>(ca);
        ::algo1<char>(0);
    }
    {
        int a = 0;
        int const ca = 0;

        ::algo1_<char>(a);
        ::algo1_<char>(ca);
        ::algo1_<char>(0);
    }
    {
        int a0 = 0, a1 = 0;
        int const ca0 = 0, ca1 = 0;

        ::algo2<char>(a0, a1);
        ::algo2<char>(a0, ca1);
        ::algo2<char>(ca0, a1);
        ::algo2<char>(ca0, ca1);
    }
}
