#include <pstade/vodka/drink.hpp>


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/egg/detail/array_resurrect.hpp>
#include <pstade/minimal_test.hpp>


#include <pstade/boost_workaround.hpp>
#include <boost/static_assert.hpp>
#include <boost/type_traits/is_array.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/type_traits/is_const.hpp>
#include <boost/mpl/assert.hpp>


template<class A>
struct klass
{
    typedef A& type;
};

template<class T, std::size_t N>
struct klass< T[N] >
{
    BOOST_STATIC_ASSERT(N == 3);
    BOOST_MPL_ASSERT((boost::is_const<T>));
    BOOST_MPL_ASSERT((boost::is_array<T[N]>));

    typedef T* type;
};


template<class A>
struct klass2 :
    klass<PSTADE_EGG_ARRAY_RESURRECT(A)>
{};

template<class A>
typename klass2<A const>::type foo(A const& a)
{
    return a;
};


void pstade_minimal_test()
{
    {
        int a[3];
        int *x = ::foo(a); // must fail to compile.
        BOOST_CHECK(x == &a[0]);
    }
}
