#ifndef BOOST_EGG_DETAIL_FUNCTION_CALL_OPERATOR_HPP
#define BOOST_EGG_DETAIL_FUNCTION_CALL_OPERATOR_HPP


// Boost.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/preprocessor/seq/enum.hpp>
#include <boost/preprocessor/seq/size.hpp>
#include <boost/egg/config.hpp> // BOOST_EGG_HAS_RVALUE_REFS
#include <boost/egg/preprocessor/seq_enum_i.hpp>
#include <boost/egg/detail/bytag_to.hpp>
#include <boost/egg/detail/eat_mutable.hpp>


#if defined(BOOST_EGG_HAS_RVALUE_REFS)


    // Neither egg::forward nor std::forward is used so that LittleFunction can take lvalues.
    #define BOOST_EGG_FUNCTION_CALL_OPERATOR(BytagSeq, Cv) \
        template<BOOST_PP_ENUM_PARAMS(BOOST_PP_SEQ_SIZE(BytagSeq), class A)> \
        typename apply_little< \
            Little BOOST_EGG_EAT_MUTABLE(Cv), \
            BOOST_EGG_PP_SEQ_ENUM_I(BytagSeq, BOOST_EGG_BYTAG_TO_DEDUCED, ~) \
        >::type \
        operator()(BOOST_EGG_PP_SEQ_ENUM_I(BytagSeq, BOOST_EGG_BYTAG_TO_PARAM, ~)) BOOST_EGG_EAT_MUTABLE(Cv) \
        { \
             return call_little(this->little(), BOOST_PP_ENUM_PARAMS(BOOST_PP_SEQ_SIZE(BytagSeq), a)); \
        } \
    /**/


#else


    #include <boost/preprocessor/seq/transform.hpp>
    #include <boost/egg/preprocessor/seq_for_each_product.hpp>


    #define BOOST_EGG_FUNCTION_CALL_OPERATOR(BytagSeq, Cv) \
        BOOST_EGG_PP_SEQ_FOR_EACH_PRODUCT( \
            BOOST_PP_SEQ_TRANSFORM(BOOST_EGG_BYTAG_TO_SEQ, ~, BytagSeq), BOOST_EGG_FUNCTION_CALL_OPERATOR_op, Cv \
        ) \
    /**/

        #define BOOST_EGG_FUNCTION_CALL_OPERATOR_op(R, BytagSeq, Cv) \
            template<BOOST_PP_ENUM_PARAMS(BOOST_PP_SEQ_SIZE(BytagSeq), class A)> \
            typename apply_little< \
                little_type BOOST_EGG_EAT_MUTABLE(Cv), \
                BOOST_EGG_PP_SEQ_ENUM_I_R(R, BytagSeq, BOOST_EGG_BYTAG_TO_DEDUCED, ~) \
            >::type \
            operator()(BOOST_EGG_PP_SEQ_ENUM_I_R(R, BytagSeq, BOOST_EGG_BYTAG_TO_PARAM, ~)) BOOST_EGG_EAT_MUTABLE(Cv) \
            { \
                return call_little(this->little(), BOOST_PP_ENUM_PARAMS(BOOST_PP_SEQ_SIZE(BytagSeq), a)); \
            } \
        /**/


#endif // defined(BOOST_EGG_HAS_RVALUE_REFS)


#endif
