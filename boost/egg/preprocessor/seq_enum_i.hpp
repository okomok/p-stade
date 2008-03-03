#ifndef BOOST_EGG_PREPROCESSOR_SEQ_ENUM_I_HPP
#define BOOST_EGG_PREPROCESSOR_SEQ_ENUM_I_HPP


// Boost.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/preprocessor/array/elem.hpp>
#include <boost/preprocessor/punctuation/comma_if.hpp>
#include <boost/preprocessor/seq/for_each_i.hpp>


#define BOOST_EGG_PP_SEQ_ENUM_I(Seq, Macro, Data) \
    BOOST_PP_SEQ_FOR_EACH_I(BOOST_EGG_PP_SEQ_ENUM_I_op, (2, (Macro, Data)), Seq) \
/**/


#define BOOST_EGG_PP_SEQ_ENUM_I_R(R, Seq, Macro, Data) \
    BOOST_PP_SEQ_FOR_EACH_I_R(R, BOOST_EGG_PP_SEQ_ENUM_I_op, (2, (Macro, Data)), Seq) \
/**/

    #define BOOST_EGG_PP_SEQ_ENUM_I_op(R, M_D, I, Elem) \
        BOOST_PP_COMMA_IF(I) BOOST_PP_ARRAY_ELEM(0, M_D)(R, BOOST_PP_ARRAY_ELEM(1, M_D), I, Elem) \
    /**/


#endif
