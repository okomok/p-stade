#ifndef BOOST_EGG_PREPROCESSOR_BITS_ENUM_DEDUCED_HPP
#define BOOST_EGG_PREPROCESSOR_BITS_ENUM_DEDUCED_HPP


// Boost.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/punctuation/comma_if.hpp>
#include <boost/preprocessor/seq/for_each_i.hpp>
#include <boost/egg/detail/deduced_const.hpp>


// (0)(1)(1) -> A0, A1 const, A2 const
#define BOOST_EGG_PP_BITS_ENUM_DEDUCED_R(R, Bits, A) \
    BOOST_PP_SEQ_FOR_EACH_I_R(R, BOOST_EGG_PP_BITS_ENUM_DEDUCED_op, A, Bits) \
/**/

    #define BOOST_EGG_PP_BITS_ENUM_DEDUCED_op(R, A, I, Bit) \
        BOOST_PP_COMMA_IF(I) \
            BOOST_PP_CAT(BOOST_EGG_PP_BITS_ENUM_DEDUCED_ac, Bit)(BOOST_PP_CAT(A, I)) \
    /**/

    #define BOOST_EGG_PP_BITS_ENUM_DEDUCED_ac0(P) P
    #define BOOST_EGG_PP_BITS_ENUM_DEDUCED_ac1(P) BOOST_EGG_DEDUCED_CONST(P)


#endif
