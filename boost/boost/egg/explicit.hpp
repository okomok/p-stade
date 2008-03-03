#ifndef BOOST_EGG_EXPLICIT_HPP
#define BOOST_EGG_EXPLICIT_HPP
#include <boost/egg/detail/prefix.hpp>


// Boost.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/preprocessor/seq/size.hpp>
#include <boost/egg/config.hpp> // BOOST_EGG_HAS_RVALUE_REFS
#include <boost/egg/detail/bytag_to.hpp>
#include <boost/egg/preprocessor/seq_enum_args.hpp>
#include <boost/egg/preprocessor/seq_enum_i.hpp>
#include <boost/egg/preprocessor/seq_enum_params.hpp>
#include <boost/egg/preprocessor/to_template_param_seq.hpp>


#if defined(BOOST_EGG_HAS_RVALUE_REFS)


    #include <boost/egg/result_of.hpp>


    #define BOOST_EGG_EXPLICIT(Name, X_, Params, BytagSeq) \
        BOOST_EGG_EXPLICIT_aux(Name, X_, BOOST_EGG_PP_TO_TEMPLATE_PARAM_SEQ(Params), BytagSeq) \
    /**/

        #define BOOST_EGG_EXPLICIT_aux(Name, X_, Params, BytagSeq) \
            template<BOOST_EGG_PP_SEQ_ENUM_PARAMS(Params, T), BOOST_PP_ENUM_PARAMS(BOOST_PP_SEQ_SIZE(BytagSeq), class A)> \
            typename boost::egg::result_of_< \
                X_<BOOST_EGG_PP_SEQ_ENUM_ARGS(Params, T)>, \
                (BOOST_EGG_PP_SEQ_ENUM_I(BytagSeq, BOOST_EGG_EXPLICIT_bytag_to_deduced, ~)) \
            >::type \
            Name(BOOST_EGG_PP_SEQ_ENUM_I(BytagSeq, BOOST_EGG_BYTAG_TO_PARAM, ~)) \
            { \
                return X_<BOOST_EGG_PP_SEQ_ENUM_ARGS(Params, T)>()( \
                    BOOST_PP_ENUM_PARAMS(BOOST_PP_SEQ_SIZE(BytagSeq), a) \
                ); \
            } \
        /**/

        #define BOOST_EGG_EXPLICIT_bytag_to_deduced(R, _, I, Bytag) \
            BOOST_EGG_BYTAG_TO_DEDUCED(R, _, I, Bytag) & \
        /**/


#else


    #include <boost/preprocessor/array/elem.hpp>
    #include <boost/preprocessor/seq/transform.hpp>
    #include <boost/egg/detail/const_overloaded.hpp>
    #include <boost/egg/detail/ns_result_of.hpp>
    #include <boost/egg/preprocessor/seq_for_each_product.hpp>


    #define BOOST_EGG_EXPLICIT(Name, X_, Params, BytagSeq) \
        BOOST_EGG_PP_SEQ_FOR_EACH_PRODUCT( \
            BOOST_PP_SEQ_TRANSFORM(BOOST_EGG_BYTAG_TO_SEQ, ~, BytagSeq), BOOST_EGG_EXPLICIT_op, (3, (Name, X_, BOOST_EGG_PP_TO_TEMPLATE_PARAM_SEQ(Params))) \
        ) \
    /**/

        #define BOOST_EGG_EXPLICIT_op(R, BytagSeq, Nm_X_P) \
            template<BOOST_EGG_PP_SEQ_ENUM_PARAMS(BOOST_PP_ARRAY_ELEM(2, Nm_X_P), T), BOOST_PP_ENUM_PARAMS(BOOST_PP_SEQ_SIZE(BytagSeq), class A)> \
            BOOST_EGG_NS_RESULT_OF( \
                (BOOST_PP_ARRAY_ELEM(1, Nm_X_P)<BOOST_EGG_PP_SEQ_ENUM_ARGS(BOOST_PP_ARRAY_ELEM(2, Nm_X_P), T)>), \
                (BOOST_PP_SEQ_SIZE(BytagSeq), (BOOST_EGG_PP_SEQ_ENUM_I_R(R, BytagSeq, BOOST_EGG_BYTAG_TO_NS_DEDUCED, ~))) \
            ) \
            BOOST_PP_ARRAY_ELEM(0, Nm_X_P)(BOOST_EGG_PP_SEQ_ENUM_I_R(R, BytagSeq, BOOST_EGG_BYTAG_TO_PARAM, ~) BOOST_EGG_CONST_OVERLOADED(BOOST_PP_SEQ_SIZE(BytagSeq), A)) \
            { \
                return BOOST_PP_ARRAY_ELEM(1, Nm_X_P)<BOOST_EGG_PP_SEQ_ENUM_ARGS(BOOST_PP_ARRAY_ELEM(2, Nm_X_P), T)>()( \
                    BOOST_PP_ENUM_PARAMS(BOOST_PP_SEQ_SIZE(BytagSeq), a) \
                ); \
            } \
        /**/


#endif // defined(BOOST_EGG_HAS_RVALUE_REFS)


#include <boost/egg/detail/suffix.hpp>
#endif
