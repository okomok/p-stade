#ifndef BOOST_EGG_PP_SEQ_ENUM_PARAMS_HPP
#define BOOST_EGG_PP_SEQ_ENUM_PARAMS_HPP


// Boost.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/punctuation/comma_if.hpp>
#include <boost/preprocessor/seq/for_each_i.hpp>


// (class)(int) -> class T0, int T1
#define BOOST_EGG_PP_SEQ_ENUM_PARAMS(ParamSeq, T) \
    BOOST_PP_SEQ_FOR_EACH_I(BOOST_EGG_PP_SEQ_ENUM_PARAMS_op, T, ParamSeq) \
/**/

    #define BOOST_EGG_PP_SEQ_ENUM_PARAMS_op(r, T, I, Elem) \
        BOOST_PP_COMMA_IF(I) Elem BOOST_PP_CAT(T, I) \
    /**/


#endif
