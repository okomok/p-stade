#ifndef BOOST_EGG_PREPROCESSOR_BITS_ENUM_BINARY_PARAMS_HPP
#define BOOST_EGG_PREPROCESSOR_BITS_ENUM_BINARY_PARAMS_HPP


// Boost.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/preprocessor/array/elem.hpp>
#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/punctuation/comma_if.hpp>
#include <boost/preprocessor/seq/for_each_i.hpp>


// (0)(1)(1) -> A0 B0, A1 const B1, A2 const B2
#define BOOST_EGG_PP_BITS_ENUM_BINARY_PARAMS_R(R, Bits, A, B) \
    BOOST_PP_SEQ_FOR_EACH_I_R(R, BOOST_EGG_PP_BITS_ENUM_BINARY_PARAMS_op, (2, (A, B)), Bits) \
/**/

    #define BOOST_EGG_PP_BITS_ENUM_BINARY_PARAMS_op(R, A_B, I, Bit) \
        BOOST_PP_COMMA_IF(I) \
            BOOST_PP_CAT(BOOST_EGG_PP_BITS_ENUM_BINARY_PARAMS_c, Bit)(BOOST_PP_CAT(BOOST_PP_ARRAY_ELEM(0, A_B), I)) \
            BOOST_PP_CAT(BOOST_PP_ARRAY_ELEM(1, A_B), I) \
    /**/

    #define BOOST_EGG_PP_BITS_ENUM_BINARY_PARAMS_c0(P) P
    #define BOOST_EGG_PP_BITS_ENUM_BINARY_PARAMS_c1(P) P const


#endif
