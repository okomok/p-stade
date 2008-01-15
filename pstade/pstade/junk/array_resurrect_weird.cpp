#include <pstade/vodka/drink.hpp>


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/egg/detail/array_resurrect.hpp>
#include <pstade/minimal_test.hpp>


#include <boost/static_assert.hpp>
#include <boost/type_traits/is_array.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/type_traits/is_const.hpp>
#include <boost/type_traits/is_volatile.hpp>
#include <boost/mpl/assert.hpp>
#include <cstddef>


template<class T>
struct rng_iterator_impl;

template<class T, std::size_t N>
struct rng_iterator_impl< T[N] >
{
    typedef T *type;
};

template<class T>
struct rng_iterator
{
    typedef typename rng_iterator_impl<PSTADE_EGG_ARRAY_RESURRECT(T)>::type type;
};

template<class T>
typename rng_iterator<T>::type bgn(T& a)
{
    return &a[0];
}

template<class T>
typename rng_iterator<T const>::type bgn(T const& a)
{
  //  return a->foo();
    return &a[0];
}


struct klass {

    template<class T>
    typename rng_iterator<T>::type bgn(T& a)
    {
        return &a[0];
    }

    template<class T>
    typename rng_iterator<T const>::type bgn(T const& a)
    {
      //  return a->foo();
        return &a[0];
    }

};


#if 0
int g_a[3] = {};
int *g_p = bgn(g_a);
#endif
//typedef rng_iterator< int[3] >::type ttt;

void pstade_minimal_test()
{
    {
        BOOST_MPL_ASSERT((boost::is_same<rng_iterator< int[3] >::type, int *>));
        int a[3] = {};
        int *p = bgn(a);
        BOOST_CHECK( p == &a[0] );
        BOOST_MPL_ASSERT((boost::is_same<rng_iterator< int[3] >::type, int *>));
    }
    {
        BOOST_MPL_ASSERT((boost::is_same<rng_iterator< int[3] >::type, int *>));
        int a[3] = {};
        int *p = klass().bgn(a);
        BOOST_CHECK( p == &a[0] );
        BOOST_MPL_ASSERT((boost::is_same<rng_iterator< int[3] >::type, int *>));
    }

    {
        typedef rng_iterator< int[3] >::type weird_t;
        typedef rng_iterator< int const[3] >::type weird_t2;
        BOOST_MPL_ASSERT((boost::is_same<rng_iterator< int const[3] >::type, int const *>));
        int const a[3] = {};
        int const *p = bgn(a);
        BOOST_CHECK( p == &a[0] );
        BOOST_MPL_ASSERT((boost::is_same<rng_iterator< int const[3] >::type, int const *>));
    }

    {
        typedef rng_iterator< int[3] >::type weird_t;
        typedef rng_iterator< int const[3] >::type weird_t2;
        BOOST_MPL_ASSERT((boost::is_same<rng_iterator< int const[3] >::type, int const *>));
        int const a[3] = {};
        int const *p = klass().bgn(a);
        BOOST_CHECK( p == &a[0] );
        BOOST_MPL_ASSERT((boost::is_same<rng_iterator< int const[3] >::type, int const *>));
    }
}
