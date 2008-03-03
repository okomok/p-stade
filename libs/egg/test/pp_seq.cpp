

// Boost.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/egg/preprocessor/seq_enum_i.hpp>
#include <boost/egg/preprocessor/seq_for_each_product.hpp>
#include "./egg_test.hpp"


#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/seq/cat.hpp>


int bar(int i, int j, int k)
{
    return i - j + k;
}


#define MACRO2(R, Data, I, Elem) (Data)Elem


#define MACRO(R, Seq, Data) \
    void BOOST_PP_CAT(foo, BOOST_PP_SEQ_CAT(Seq))() \
    { \
        Data i = BOOST_PP_SEQ_CAT(Seq); \
        (void)i; \
        ::bar( BOOST_EGG_PP_SEQ_ENUM_I_R(R, Seq, MACRO2, int) ); \
    } \
/**/

BOOST_EGG_PP_SEQ_FOR_EACH_PRODUCT( ((1)(2)) ((0)) ((3)(4)) , MACRO, long)


#define MACRO3(R, Data, I, Elem) Elem + I

void egg_test()
{
    BOOST_CHECK( (2+0)-(1+1)+(4+2) == ::bar( BOOST_EGG_PP_SEQ_ENUM_I((2)(1)(4), MACRO3, int) ) );
}
