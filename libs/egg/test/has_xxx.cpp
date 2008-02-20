

// Boost.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/egg/detail/has_xxx.hpp>
#include "./egg_test.hpp"


#include <boost/mpl/assert.hpp>


namespace nested_type
{

    // for weird compilers
    // http://lists.boost.org/Archives/boost/2005/10/95809.php
    template<typename T>
    struct X
    {
        typedef int xxx;
    };

    BOOST_EGG_HAS_XXX(xxx)


    struct a1 {};
    struct a2 { void xxx(); };
    struct a3 { int xxx; };
    struct a4 { static int xxx(); };
    struct a5 { template< typename T > struct xxx {}; };

    struct b1 { typedef int xxx; };
    struct b2 { struct xxx; };
    struct b3 { typedef int& xxx; };
    struct b4 { typedef int* xxx; };
    struct b5 { typedef int xxx[10]; };
    struct b6 { typedef void (*xxx)(); };
    struct b7 { typedef void (xxx)(); };

    template< typename T > struct outer;
    template< typename T > struct inner { typedef typename T::type type; };


    BOOST_MPL_ASSERT_NOT(( has_xxx<int> ));
    BOOST_MPL_ASSERT_NOT(( has_xxx<int&> ));
    BOOST_MPL_ASSERT_NOT(( has_xxx<int*> ));
    BOOST_MPL_ASSERT_NOT(( has_xxx<int[5]> ));
    BOOST_MPL_ASSERT_NOT(( has_xxx<int(&)[5]> ));
    BOOST_MPL_ASSERT_NOT(( has_xxx<int(*)[5]> ));
    BOOST_MPL_ASSERT_NOT(( has_xxx<int (*)()> ));
    BOOST_MPL_ASSERT_NOT(( has_xxx<int ()> ));
    BOOST_MPL_ASSERT_NOT(( has_xxx<int (&)()> ));
    BOOST_MPL_ASSERT_NOT(( has_xxx<int (*)(int)> ));
    BOOST_MPL_ASSERT_NOT(( has_xxx<int (int)> ));
    BOOST_MPL_ASSERT_NOT(( has_xxx<int (&)(int)> ));

    BOOST_MPL_ASSERT_NOT(( has_xxx<a2> ));
    BOOST_MPL_ASSERT_NOT(( has_xxx<a3> ));
    BOOST_MPL_ASSERT_NOT(( has_xxx<a4> ));
    BOOST_MPL_ASSERT_NOT(( has_xxx<a5> )); // vc8, vc7.1
    BOOST_MPL_ASSERT_NOT(( has_xxx<a1> ));
    BOOST_MPL_ASSERT_NOT(( has_xxx< outer< inner<int> > > ));

    BOOST_MPL_ASSERT(( has_xxx<b1> ));
    BOOST_MPL_ASSERT(( has_xxx<b2> ));
    BOOST_MPL_ASSERT(( has_xxx<b3> ));
    BOOST_MPL_ASSERT(( has_xxx<b4> ));
    BOOST_MPL_ASSERT(( has_xxx<b5> )); // vc8
    BOOST_MPL_ASSERT(( has_xxx<b6> ));
    BOOST_MPL_ASSERT(( has_xxx<b7> )); // vc8, gcc
}


void egg_test()
{ }
