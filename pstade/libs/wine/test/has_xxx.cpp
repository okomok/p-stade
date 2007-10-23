#include <pstade/vodka/drink.hpp>


// PStade.Wine
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// for weird compilers
// http://lists.boost.org/Archives/boost/2005/10/95809.php
#include <boost/mpl/modulus.hpp>
#include <boost/mpl/apply.hpp>


#include <pstade/has_xxx.hpp>
#include <boost/test/minimal.hpp>


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

    PSTADE_HAS_TYPE(xxx)


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
    //BOOST_MPL_ASSERT_NOT(( has_xxx<a5> )); // vc8, vc7.1
    BOOST_MPL_ASSERT_NOT(( has_xxx<a1> ));
    BOOST_MPL_ASSERT_NOT(( has_xxx< outer< inner<int> > > ));

    BOOST_MPL_ASSERT(( has_xxx<b1> ));
    BOOST_MPL_ASSERT(( has_xxx<b2> ));
    BOOST_MPL_ASSERT(( has_xxx<b3> ));
    BOOST_MPL_ASSERT(( has_xxx<b4> ));
    // BOOST_MPL_ASSERT(( has_xxx<b5> )); // vc8
    BOOST_MPL_ASSERT(( has_xxx<b6> ));
    // BOOST_MPL_ASSERT(( has_xxx<b7> )); // vc8, gcc
}



namespace data_member {

    // for weird compilers
    // http://lists.boost.org/Archives/boost/2005/10/95809.php
    template<typename T>
    struct X
    {
        typedef int xxx;
    };

    PSTADE_HAS_DATA(int, xxx)


    struct a1 {};
    struct a2 { void xxx(); };
    struct a3 { int xxx; char y; };
    struct a4 { static int xxx(); };
    struct a5 { template< typename T > struct xxx {}; };
    struct a6 { double xxx; };

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
    BOOST_MPL_ASSERT_NOT(( has_xxx<int[]> ));
    BOOST_MPL_ASSERT_NOT(( has_xxx<int (*)()> ));

    BOOST_MPL_ASSERT_NOT(( has_xxx<a2> ));
    BOOST_MPL_ASSERT(( has_xxx<a3> ));
    BOOST_MPL_ASSERT_NOT(( has_xxx<a4> ));
    BOOST_MPL_ASSERT_NOT(( has_xxx<a5> ));
    BOOST_MPL_ASSERT_NOT(( has_xxx<a1> ));
    BOOST_MPL_ASSERT_NOT(( has_xxx< outer< inner<int> > > ));
    BOOST_MPL_ASSERT_NOT(( has_xxx<a6> ));

    // they no longer fails, but are not precise.
    BOOST_MPL_ASSERT_NOT(( has_xxx<b1> )); // vc7.1
    BOOST_MPL_ASSERT_NOT(( has_xxx<b2> ));
    BOOST_MPL_ASSERT_NOT(( has_xxx<b3> )); // vc7.1
    BOOST_MPL_ASSERT_NOT(( has_xxx<b4> )); // vc7.1
    BOOST_MPL_ASSERT_NOT(( has_xxx<b5> )); // vc7.1
    BOOST_MPL_ASSERT_NOT(( has_xxx<b6> )); // vc7.1
    BOOST_MPL_ASSERT_NOT(( has_xxx<b7> )); // vc7.1
}


namespace mem_fun {

    // for weird compilers
    // http://lists.boost.org/Archives/boost/2005/10/95809.php
    template<typename T>
    struct X
    {
        typedef int xxx;
    };

    PSTADE_HAS_FUNCTION(int, xxx, (int)(double))


    struct a1 {};
    struct a2 { void xxx(); };
    struct a3 { int xxx(int, double); char y; };
    struct a4 { static int xxx(); };
    struct a5 { template< typename T > struct xxx {}; };
    struct a6 { double xxx; };
    struct a7 { int xxx(int); };
    struct a8 { void xxx(int, double); };
    struct a9 { static int xxx(int, double); };

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
    BOOST_MPL_ASSERT_NOT(( has_xxx<int[]> ));
    BOOST_MPL_ASSERT_NOT(( has_xxx<int (*)()> ));

    BOOST_MPL_ASSERT_NOT(( has_xxx<a2> ));
    BOOST_MPL_ASSERT(( has_xxx<a3> ));
    BOOST_MPL_ASSERT_NOT(( has_xxx<a4> ));
    BOOST_MPL_ASSERT_NOT(( has_xxx<a5> ));
    BOOST_MPL_ASSERT_NOT(( has_xxx<a1> ));
    BOOST_MPL_ASSERT_NOT(( has_xxx< outer< inner<int> > > ));
    BOOST_MPL_ASSERT_NOT(( has_xxx<a6> ));
    BOOST_MPL_ASSERT_NOT(( has_xxx<a7> ));
    BOOST_MPL_ASSERT_NOT(( has_xxx<a8> ));
    BOOST_MPL_ASSERT_NOT(( has_xxx<a9> ));

    // they no longer fails, but are not precise.
    BOOST_MPL_ASSERT_NOT(( has_xxx<b1> )); // vc7.1
    BOOST_MPL_ASSERT_NOT(( has_xxx<b2> ));
    BOOST_MPL_ASSERT_NOT(( has_xxx<b3> )); // vc7.1
    BOOST_MPL_ASSERT_NOT(( has_xxx<b4> )); // vc7.1
    BOOST_MPL_ASSERT_NOT(( has_xxx<b5> )); // vc7.1
    BOOST_MPL_ASSERT_NOT(( has_xxx<b6> )); // vc7.1
    BOOST_MPL_ASSERT_NOT(( has_xxx<b7> )); // vc7.1
}


int test_main(int, char*[])
{
    return 0;
}
