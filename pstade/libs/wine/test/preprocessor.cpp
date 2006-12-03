#include <pstade/vodka/drink.hpp>
#include <boost/test/minimal.hpp>


// PStade.Wine
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/preprocessor.hpp>


#include <boost/preprocessor/repetition/enum_params.hpp>


template< BOOST_PP_ENUM_PARAMS(5, class A) >
void foo( PSTADE_PP_ENUM_REF_PARAMS_WITH_VARS(5, A, a) )
{
    return;
}

template< BOOST_PP_ENUM_PARAMS(5, class A) >
void foo_( PSTADE_PP_ENUM_REF_PARAMS(5, A) )
{
    return;
}


template< BOOST_PP_ENUM_PARAMS(5, class A) >
void cfoo( PSTADE_PP_ENUM_CREF_PARAMS_WITH_VARS(5, A, a) )
{
    return;
}


template< BOOST_PP_ENUM_PARAMS(5, class A) >
void cfoo_( PSTADE_PP_ENUM_CREF_PARAMS(5, A) )
{
    return;
}


void test()
{
    int i = 0;
    ::foo(i, i, i, i, i);
    ::foo_(i, i, i, i, i);

    ::cfoo(1, 1, 1, 1, 1);
    ::cfoo_(1, 1, 1, 1, 1);
}


int test_main(int, char*[])
{
    ::test();
    return 0;
}
