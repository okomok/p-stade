#include <pstade/vodka/drink.hpp>
#include <boost/test/minimal.hpp>


// PStade.P_Stade
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/mpl/integral_c.hpp>


#define MACRO_THREE 3


int const const_three = 3;


struct mpl_three :
    boost::mpl::integral_c<int, 3>
{ };


template< class T, T v >
struct static_c
{
    static T const value = v;
};

template< class T, T v >
T const
static_c<T, v>::value;


struct three :
    static_c<int, 3>
{ };


inline
void foo(int const& x)
{
    BOOST_CHECK( x == 3 );
}


template< class T >
void bar()
{
    ::foo(MACRO_THREE);  // ok
    ::foo(const_three);  // possible ODR violation
    ::foo(mpl_three::value); // link error
    ::foo(three::value); // ok
}


void test()
{
    ::bar<int>();
}


int test_main(int, char*[])
{
    ::test();

    return 0;
}

