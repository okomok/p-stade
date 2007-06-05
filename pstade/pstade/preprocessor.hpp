#ifndef PSTADE_PREPROCESSOR_HPP
#define PSTADE_PREPROCESSOR_HPP
#include "./prelude.hpp"


// PStade.Wine
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/comparison/equal.hpp>
#include <boost/preprocessor/control/iif.hpp>
#include <boost/preprocessor/detail/is_unary.hpp>
#include <boost/preprocessor/facilities/intercept.hpp>
#include <boost/preprocessor/punctuation/comma_if.hpp>
#include <boost/preprocessor/repetition/enum_binary_params.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/preprocessor/repetition/repeat.hpp>
#include <boost/preprocessor/repetition/repeat_from_to.hpp>
#include <boost/preprocessor/seq/elem.hpp>
#include <boost/preprocessor/seq/for_each.hpp>
#include <boost/preprocessor/seq/for_each_i.hpp>
#include <boost/preprocessor/seq/pop_back.hpp>
#include <boost/preprocessor/seq/size.hpp>
#include <boost/preprocessor/tuple/eat.hpp>


// utility
//

#define PSTADE_PP_CAT3(A0, A1, A2) \
    BOOST_PP_CAT(A0, BOOST_PP_CAT(A1, A2)) \
/**/


// parameter
//

#define PSTADE_PP_ENUM_PARAMS_WITH(Size, Param, A) \
    BOOST_PP_ENUM_BINARY_PARAMS(Size, Param, A BOOST_PP_INTERCEPT) \
/**/


// sequence
//

#define PSTADE_PP_SEQ_IS_SEQ \
    BOOST_PP_IS_UNARY \
/**/


#define PSTADE_PP_SEQ_BACK(Seq) \
    BOOST_PP_SEQ_ELEM(BOOST_PP_DEC(BOOST_PP_SEQ_SIZE(Seq)), Seq) \
/**/


// Seq -> Seq Seq .. Seq
#define PSTADE_PP_SEQ_CYCLE(Seq, Size) \
    BOOST_PP_REPEAT(Size, PSTADE_PP_SEQ_cycle, Seq) \
/**/

    #define PSTADE_PP_SEQ_cycle(z, N, Seq) \
        Seq \
    /**/


// A -> (A)(A)..(A)
#define PSTADE_PP_SEQ_REPEAT(A, Size) \
    PSTADE_PP_SEQ_CYCLE((A), Size) \
/**/


// A -> (A0)(A1)..(AN)
#define PSTADE_PP_SEQ_PARAMS(N, A) \
    BOOST_PP_REPEAT(N, PSTADE_PP_SEQ_params, A) \
/**/

    #define PSTADE_PP_SEQ_params(z, N, A) \
        (BOOST_PP_CAT(A, N)) \
    /**/


// (1, 5) -> (1)(2)(3)(4)
#define PSTADE_PP_SEQ_RANGE(N, M) \
    BOOST_PP_REPEAT_FROM_TO(N, M, PSTADE_PP_SEQ_range, ~) \
/**/

    #define PSTADE_PP_SEQ_range(z, N, _) \
        (N) \
    /**/


#define PSTADE_PP_SEQ_MAYBE_TO(MaybeSeq, Seq) \
    BOOST_PP_IIF( PSTADE_PP_SEQ_IS_SEQ(MaybeSeq), \
        MaybeSeq, \
        Seq \
    )
/**/


// type system
//

#define PSTADE_PP_DECLARE_TYPE(Struct, NameSeq) \
    PSTADE_PP_NAMESPACE_OPEN(NameSeq) \
        Struct PSTADE_PP_SEQ_BACK(NameSeq); \
    PSTADE_PP_NAMESPACE_CLOSE(NameSeq) \
/**/


#define PSTADE_PP_DECLARE_TEMPLATE(Struct, NameSeq, ParamSeqOrCount) \
    PSTADE_PP_NAMESPACE_OPEN(NameSeq) \
        template< PSTADE_PP_TO_TEMPLATE_PARAMS(PSTADE_PP_TO_TEMPLATE_PARAM_SEQ(ParamSeqOrCount), T) > \
        Struct PSTADE_PP_SEQ_BACK(NameSeq); \
    PSTADE_PP_NAMESPACE_CLOSE(NameSeq) \
/**/


// (class)(int) -> class T0, int T1
#define PSTADE_PP_TO_TEMPLATE_PARAMS(ParamSeq, T) \
    BOOST_PP_SEQ_FOR_EACH_I(PSTADE_PP_TO_TEMPLATE_PARAMS_op, T, ParamSeq) \
/**/

    #define PSTADE_PP_TO_TEMPLATE_PARAMS_op(r, T, I, Elem) \
        BOOST_PP_COMMA_IF(I) Elem BOOST_PP_CAT(T, I) \
    /**/


// (class)(int) -> T0, T1
#define PSTADE_PP_TO_TEMPLATE_ARGS(ParamSeq, T) \
    BOOST_PP_ENUM_PARAMS(BOOST_PP_SEQ_SIZE(ParamSeq), T) \
/**/


// Same as 'BOOST_TYPEOF_TOSEQ' at <boost/typeof/template_encoding.hpp>
// (class)(int) -> as is; 2 -> (class)(class)
#define PSTADE_PP_TO_TEMPLATE_PARAM_SEQ(ParamSeqOrCount) \
    BOOST_PP_IIF( PSTADE_PP_SEQ_IS_SEQ(ParamSeqOrCount), \
        ParamSeqOrCount BOOST_PP_TUPLE_EAT(3), \
        BOOST_PP_REPEAT \
    )(ParamSeqOrCount, PSTADE_PP_TO_TEMPLATE_PARAM_SEQ_op, ~) \
/**/

    #define PSTADE_PP_TO_TEMPLATE_PARAM_SEQ_op(z, N, _) \
        (class) \
    /**/


// (aaa) -> nothing, (aaa)(bbb) -> namespace aaa {
#define PSTADE_PP_NAMESPACE_OPEN(NameSeq) \
    BOOST_PP_IIF( BOOST_PP_EQUAL(BOOST_PP_SEQ_SIZE(NameSeq), 1), \
        BOOST_PP_TUPLE_EAT(2), \
        PSTADE_PP_for_each_without_back \
    )(PSTADE_PP_NAMESPACE_OPEN_op, NameSeq)
/**/

    #define PSTADE_PP_for_each_without_back(Op, NameSeq) \
        BOOST_PP_SEQ_FOR_EACH(Op, ~, BOOST_PP_SEQ_POP_BACK(NameSeq)) \
    /**/

        #define PSTADE_PP_NAMESPACE_OPEN_op(r, _, Elem) \
            namespace Elem { \
        /**/


// (aaa) -> nothing, (aaa)(bbb) -> }
#define PSTADE_PP_NAMESPACE_CLOSE(NameSeq) \
    BOOST_PP_IIF( BOOST_PP_EQUAL(BOOST_PP_SEQ_SIZE(NameSeq), 1), \
        BOOST_PP_TUPLE_EAT(2), \
        PSTADE_PP_for_each_without_back \
    )(PSTADE_PP_NAMESPACE_CLOSE_op, NameSeq)
/**/

    #define PSTADE_PP_NAMESPACE_CLOSE_op(r, _, Elem) \
        } \
    /**/


// (aaa)(bbb) -> ::aaa::bbb
#define PSTADE_PP_FULLNAME(NameSeq) \
    BOOST_PP_SEQ_FOR_EACH(PSTADE_PP_scope_op, ~, NameSeq) \
/**/

    #define PSTADE_PP_scope_op(r, _, Elem) \
        ::Elem \
    /**/


// int
//

#define PSTADE_PP_INT_0  0
#define PSTADE_PP_INT_1  1
#define PSTADE_PP_INT_2  2
#define PSTADE_PP_INT_3  3
#define PSTADE_PP_INT_4  4
#define PSTADE_PP_INT_5  5
#define PSTADE_PP_INT_6  6
#define PSTADE_PP_INT_7  7
#define PSTADE_PP_INT_8  8
#define PSTADE_PP_INT_9  9
#define PSTADE_PP_INT_10 10
#define PSTADE_PP_INT_11 11
#define PSTADE_PP_INT_12 12
#define PSTADE_PP_INT_13 13
#define PSTADE_PP_INT_14 14
#define PSTADE_PP_INT_15 15
#define PSTADE_PP_INT_16 16
#define PSTADE_PP_INT_17 17
#define PSTADE_PP_INT_18 18
#define PSTADE_PP_INT_19 19


#endif
