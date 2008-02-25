#ifndef BOOST_EGG_PREPROCESSOR_FOR_EACH_BY_PERFECT_HPP
#define BOOST_EGG_PREPROCESSOR_FOR_EACH_BY_PERFECT_HPP


// Boost.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// Copyright David Abrahams 2006. Distributed under the Boost
// Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)


#include <boost/preprocessor/array/elem.hpp>
#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/seq/for_each_i.hpp>
#include <boost/preprocessor/seq/for_each_product.hpp>
#include <boost/preprocessor/seq/seq.hpp> // HEAD, TAIL
#include <boost/egg/detail/deduced_const.hpp>
#include <boost/egg/preprocessor/seq_repeat.hpp>


#define BOOST_EGG_PP_FOR_EACH_BY_PERFECT(Count, Param, Macro, Data) \
    BOOST_PP_SEQ_FOR_EACH_PRODUCT(BOOST_EGG_PP_FOR_EACH_BY_PERFECT_op, (((3, (Param, Macro, Data))))BOOST_EGG_PP_SEQ_REPEAT((0)(1), Count)) \
/**/


    // If msvc-7.1 array had no bug, `_reference` would be unneeded.
    #define BOOST_EGG_PP_FOR_EACH_BY_PERFECT_op(R, A_BitSeq) \
        BOOST_EGG_PP_FOR_EACH_BY_PERFECT_macro(A_BitSeq) \
            ( \
                R, \
                BOOST_EGG_PP_FOR_EACH_BY_PERFECT_data(A_BitSeq), \
                BOOST_EGG_PP_FOR_EACH_BY_PERFECT_for_each(R, BOOST_EGG_PP_FOR_EACH_BY_PERFECT_qualified, A_BitSeq), \
                BOOST_EGG_PP_FOR_EACH_BY_PERFECT_for_each(R, BOOST_EGG_PP_FOR_EACH_BY_PERFECT_reference, A_BitSeq) \
            ) \
    /**/

    #define BOOST_EGG_PP_FOR_EACH_BY_PERFECT_param(A_BitSeq) BOOST_PP_ARRAY_ELEM(0, BOOST_PP_SEQ_HEAD(A_BitSeq))
    #define BOOST_EGG_PP_FOR_EACH_BY_PERFECT_macro(A_BitSeq) BOOST_PP_ARRAY_ELEM(1, BOOST_PP_SEQ_HEAD(A_BitSeq))
    #define BOOST_EGG_PP_FOR_EACH_BY_PERFECT_data(A_BitSeq)  BOOST_PP_ARRAY_ELEM(2, BOOST_PP_SEQ_HEAD(A_BitSeq))

    #define BOOST_EGG_PP_FOR_EACH_BY_PERFECT_for_each(R, Macro, A_BitSeq) \
        BOOST_PP_SEQ_FOR_EACH_I_R(R, Macro, BOOST_EGG_PP_FOR_EACH_BY_PERFECT_param(A_BitSeq), BOOST_PP_SEQ_TAIL(A_BitSeq)) \
    /**/

    // (Param0)(Param1 const)(Param2)...
    #define BOOST_EGG_PP_FOR_EACH_BY_PERFECT_qualified(R, Param, I, Bit) \
        ( BOOST_PP_CAT(BOOST_EGG_PP_FOR_EACH_BY_PERFECT_ac, Bit)(BOOST_PP_CAT(Param, I)) ) \
    /**/

    // (Param0 &)(Param1 const &)(Param2 &)...
    #define BOOST_EGG_PP_FOR_EACH_BY_PERFECT_reference(R, Param, I, Bit) \
        ( BOOST_PP_CAT(Param, I) BOOST_PP_CAT(BOOST_EGG_PP_FOR_EACH_BY_PERFECT_c, Bit) & ) \
    /**/

    #define BOOST_EGG_PP_FOR_EACH_BY_PERFECT_c0
    #define BOOST_EGG_PP_FOR_EACH_BY_PERFECT_c1 const

    #define BOOST_EGG_PP_FOR_EACH_BY_PERFECT_ac0(Param) Param
    #define BOOST_EGG_PP_FOR_EACH_BY_PERFECT_ac1(Param) BOOST_EGG_DEDUCED_CONST(Param)


#endif
