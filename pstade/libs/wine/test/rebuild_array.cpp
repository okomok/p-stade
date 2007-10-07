#include <pstade/vodka/drink.hpp>


// PStade.Wine
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/rebuild_array.hpp>
#include <pstade/minimal_test.hpp>

#include <pstade/test.hpp>
#include <boost/type_traits/remove_cv.hpp>
#include <boost/type_traits/remove_pointer.hpp>
#include <boost/type_traits/add_const.hpp>
#include <boost/type_traits/is_const.hpp>
#include <boost/static_assert.hpp>


using namespace pstade;


BOOST_MPL_ASSERT((boost::is_same<rebuild_array<int[3]>::type, int[3]>));
BOOST_MPL_ASSERT((boost::is_same<rebuild_array<int const[3]>::type, int const[3]>));
BOOST_MPL_ASSERT((boost::is_same<rebuild_array<int>::type, int>));
BOOST_MPL_ASSERT((boost::is_same<rebuild_array<int const>::type, int const>));


template<class X>
struct wrap2;

template<class T, std::size_t N>
struct wrap2<T[N]>
{
    typedef T *type;
};

template<class T>
struct wrap2<T[10]>
{
    typedef int type;
};


template<class X>
struct wrap :
    wrap2<typename rebuild_array<X>::type>
{};


template<class X>
typename wrap<X const>::type
foo(X const &)
{
    return 0;
}


template<class X, class Sig = void(X)>
struct wrap123_;

template<class X, class T>
struct wrap123_<X, void(T[])>
{
//    BOOST_STATIC_ASSERT((boost::is_const<X>::value));

//    typedef typename rebuild_array<X>::type x_t;
//    BOOST_MPL_ASSERT((boost::is_const<x_t>));
    BOOST_MPL_ASSERT((boost::is_same<typename boost::remove_cv<T>::type, int>));
    typedef T *type;
//    BOOST_MPL_ASSERT((boost::is_same<T, int const>));
//    BOOST_MPL_ASSERT((boost::is_const<typename boost::remove_pointer<type>::type>));
};


template<class X>
struct wrap123 :
    wrap123_<X>
{};

template<class X>
typename wrap123<X const>::type
foo123(X const &)
{
    return 0;
}


void pstade_minimal_test()
{
    {
        int a[5];
        int const *r = ::foo(a);
        BOOST_CHECK(r == 0);
    }
    {
        int a[10];
        int r = ::foo(a);
        BOOST_CHECK(r == 0);
    }
    {
        int a[123] = {};
        int const *p = ::foo123(a);
//        ::foo123(a);
    }
}
