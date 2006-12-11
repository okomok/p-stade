#ifndef PSTADE_PREPROCESSOR_HPP
#define PSTADE_PREPROCESSOR_HPP


// PStade.Wine
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/mpl/aux_/preprocessor/is_seq.hpp>
#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/comparison/equal.hpp>
#include <boost/preprocessor/control/iif.hpp>
#include <boost/preprocessor/facilities/intercept.hpp>
#include <boost/preprocessor/punctuation/comma_if.hpp>
#include <boost/preprocessor/repetition/enum_binary_params.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/preprocessor/repetition/repeat.hpp>
#include <boost/preprocessor/seq/elem.hpp>
#include <boost/preprocessor/seq/for_each.hpp>
#include <boost/preprocessor/seq/for_each_i.hpp>
#include <boost/preprocessor/seq/pop_back.hpp>
#include <boost/preprocessor/seq/size.hpp>
#include <boost/preprocessor/tuple/eat.hpp>


// utility


// 'BOOST_PP_SEQ_CAT' isn't ugly?
#define PSTADE_PP_CAT3(A0, A1, A2) \
    BOOST_PP_CAT(A0, BOOST_PP_CAT(A1, A2)) \
/**/


// parameter


#define PSTADE_PP_ENUM_REF_PARAMS(Size, Param) \
    BOOST_PP_ENUM_BINARY_PARAMS(Size, Param, & BOOST_PP_INTERCEPT) \
/**/

#define PSTADE_PP_ENUM_REF_PARAMS_WITH_OBJECTS(Size, Param, Arg) \
    BOOST_PP_ENUM_BINARY_PARAMS(Size, Param, & Arg) \
/**/


// If 'Param' is template parameter and deduced as array type,
// VC++7.1 might break down. Take care.
#define PSTADE_PP_ENUM_CREF_PARAMS(Size, Param) \
    BOOST_PP_ENUM_BINARY_PARAMS(Size, Param, const& BOOST_PP_INTERCEPT) \
/**/

#define PSTADE_PP_ENUM_CREF_PARAMS_WITH_OBJECTS(Size, Param, Arg) \
    BOOST_PP_ENUM_BINARY_PARAMS(Size, Param, const& Arg) \
/**/


// sequence helper


#define PSTADE_PP_SEQ_BACK(Seq) \
    BOOST_PP_SEQ_ELEM(BOOST_PP_DEC(BOOST_PP_SEQ_SIZE(Seq)), Seq) \
/**/


#define PSTADE_PP_SEQ_REPLICATE(Size, A) \
    BOOST_PP_REPEAT(Size, PSTADE_PP_SEQ_REPLICATE_op, A) \
/**/

    #define PSTADE_PP_SEQ_REPLICATE_op(Z, N, A) \
        (A) \
    /**/


#define PSTADE_PP_SEQ_CYCLE(Size, Seq) \
    BOOST_PP_REPEAT(Size, PSTADE_PP_SEQ_CYCLE_op, Seq) \
/**/

    #define PSTADE_PP_SEQ_CYCLE_op(Z, N, Seq) \
        Seq \
    /**/


// type system


#define PSTADE_PP_DECLARE_TYPE(Struct, NameSeq) \
    PSTADE_PP_NAMESPACE_OPEN(NameSeq) \
        Struct PSTADE_PP_SEQ_BACK(NameSeq); \
    PSTADE_PP_NAMESPACE_CLOSE(NameSeq) \
/**/


#define PSTADE_PP_DECLARE_TEMPLATE(Struct, NameSeq, ParamSeqOrCount) \
    PSTADE_PP_NAMESPACE_OPEN(NameSeq) \
        template< PSTADE_PP_TO_TEMPLATE_PARAMS(PSTADE_PP_TO_TEMPLATE_PARAM_SEQ(ParamSeqOrCount)) > \
        Struct PSTADE_PP_SEQ_BACK(NameSeq); \
    PSTADE_PP_NAMESPACE_CLOSE(NameSeq) \
/**/


// (class)(int) -> class T0, int T1
#define PSTADE_PP_TO_TEMPLATE_PARAMS(ParamSeq) \
    BOOST_PP_SEQ_FOR_EACH_I(PSTADE_PP_TO_TEMPLATE_PARAMS_op, ~, ParamSeq) \
/**/

    #define PSTADE_PP_TO_TEMPLATE_PARAMS_op(R, _, I, Elem) \
        BOOST_PP_COMMA_IF(I) Elem BOOST_PP_CAT(T, I) \
    /**/


// (class)(int) -> T0, T1
#define PSTADE_PP_TO_TEMPLATE_ARGS(ParamSeq) \
    BOOST_PP_ENUM_PARAMS(BOOST_PP_SEQ_SIZE(ParamSeq), T) \
/**/


// (class)(int) -> as is; 2 -> (class)(class)
#define PSTADE_PP_TO_TEMPLATE_PARAM_SEQ(ParamSeqOrCount) \
    BOOST_PP_IIF( BOOST_MPL_PP_IS_SEQ(ParamSeqOrCount), \
        ParamSeqOrCount BOOST_PP_TUPLE_EAT(3), \
        BOOST_PP_REPEAT \
    )(ParamSeqOrCount, PSTADE_PP_TO_TEMPLATE_PARAM_SEQ_op, ~) \
/**/

    #define PSTADE_PP_TO_TEMPLATE_PARAM_SEQ_op(Z, N, _) \
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

        #define PSTADE_PP_NAMESPACE_OPEN_op(R, _, Elem) \
            namespace Elem { \
        /**/


// (aaa) -> nothing, (aaa)(bbb) -> }
#define PSTADE_PP_NAMESPACE_CLOSE(NameSeq) \
    BOOST_PP_IIF( BOOST_PP_EQUAL(BOOST_PP_SEQ_SIZE(NameSeq), 1), \
        BOOST_PP_TUPLE_EAT(2), \
        PSTADE_PP_for_each_without_back \
    )(PSTADE_PP_NAMESPACE_CLOSE_op, NameSeq)
/**/

    #define PSTADE_PP_NAMESPACE_CLOSE_op(R, _, Elem) \
        } \
    /**/


// (aaa)(bbb) -> ::aaa::bbb
#define PSTADE_PP_FULLNAME(NameSeq) \
    BOOST_PP_SEQ_FOR_EACH(PSTADE_PP_scope_op, ~, NameSeq) \
/**/

    #define PSTADE_PP_scope_op(R, _, Elem) \
        ::Elem \
    /**/


#endif
