#ifndef BOOST_EGG_DETAIL_FUNCTION_CALL_OPERATOR_BY_PERFECT_HPP
#define BOOST_EGG_DETAIL_FUNCTION_CALL_OPERATOR_BY_PERFECT_HPP


// Boost.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// Copyright David Abrahams 2006. Distributed under the Boost
// Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)


#include <boost/egg/config.hpp> // BOOST_EGG_HAS_RVALUE_REFS


#if defined(BOOST_EGG_HAS_RVALUE_REFS)


    #include <boost/preprocessor/facilities/intercept.hpp>
    #include <boost/preprocessor/repetition/enum_binary_params.hpp>
    #include <boost/preprocessor/repetition/enum_trailing_binary_params.hpp>
    #include <boost/preprocessor/repetition/enum_trailing_params.hpp>
    #include <boost/type_traits/remove_reference.hpp>
    #include <boost/egg/preprocessor/enum_template_params.hpp>


    #define BOOST_EGG_FUNCTION_CALL_OPERATOR_BY_PERFECT(N) \
        BOOST_EGG_PP_ENUM_TEMPLATE_PARAMS(N, class A) \
        typename apply_little< \
            little_type const \
            BOOST_PP_ENUM_TRAILING_BINARY_PARAMS(N, typename remove_reference<A, >::type BOOST_PP_INTERCEPT) \
        >::type \
        operator()(BOOST_PP_ENUM_BINARY_PARAMS(N, A, &&a)) const \
        { \
            return call_little(this->little() BOOST_PP_ENUM_TRAILING_PARAMS(N, a)); \
        } \
    /**/


#else


    #include <boost/preprocessor/cat.hpp>
    #include <boost/preprocessor/control/if.hpp>
    #include <boost/preprocessor/punctuation/comma_if.hpp>
    #include <boost/preprocessor/repetition/enum_params.hpp>
    #include <boost/preprocessor/seq/for_each_i.hpp>
    #include <boost/preprocessor/seq/for_each_product.hpp>
    #include <boost/preprocessor/seq/seq.hpp> // HEAD, TAIL
    #include <boost/preprocessor/seq/size.hpp>
    #include <boost/preprocessor/tuple/eat.hpp>
    #include <boost/egg/preprocessor/seq_repeat.hpp>
    #include <boost/egg/detail/deduced_const.hpp>


    #define BOOST_EGG_FUNCTION_CALL_OPERATOR_BY_PERFECT(N, Cv) \
        BOOST_PP_IF( N, \
            BOOST_PP_SEQ_FOR_EACH_PRODUCT, \
            BOOST_EGG_FUNCTION_CALL_OPERATOR_BY_PERFECT0(Cv) BOOST_PP_TUPLE_EAT(2) \
        )(BOOST_EGG_FUNCTION_CALL_OPERATOR_BY_PERFECT_aux, ((Cv))BOOST_EGG_PP_SEQ_REPEAT((0)(1), N)) \
    /**/

        #define BOOST_EGG_FUNCTION_CALL_OPERATOR_BY_PERFECT0(Cv) \
            typename apply_little<little_type Cv>::type \
            operator()() Cv \
            { \
                return call_little(this->little()); \
            } \
        /**/

        #define BOOST_EGG_FUNCTION_CALL_OPERATOR_BY_PERFECT_aux(R, Cv_BitSeq) \
            BOOST_EGG_FUNCTION_CALL_OPERATOR_BY_PERFECT_aux_( \
                BOOST_PP_SEQ_SIZE(BOOST_PP_SEQ_TAIL(Cv_BitSeq)), \
                BOOST_PP_SEQ_HEAD(Cv_BitSeq), \
                BOOST_PP_SEQ_FOR_EACH_I_R(R, BOOST_EGG_FUNCTION_CALL_OPERATOR_BY_PERFECT_arg_type, ~, BOOST_PP_SEQ_TAIL(Cv_BitSeq)), \
                BOOST_PP_SEQ_FOR_EACH_I_R(R, BOOST_EGG_FUNCTION_CALL_OPERATOR_BY_PERFECT_param,    ~, BOOST_PP_SEQ_TAIL(Cv_BitSeq)) \
            ) \
        /**/

        #define BOOST_EGG_FUNCTION_CALL_OPERATOR_BY_PERFECT_aux_(N, Cv, ArgTypes, Params) \
            template<BOOST_PP_ENUM_PARAMS(N, class A)> \
            typename apply_little<little_type Cv, ArgTypes>::type \
            operator()(Params) Cv \
            { \
                return call_little(this->little(), BOOST_PP_ENUM_PARAMS(N, a)); \
            } \
        /**/

        #define BOOST_EGG_FUNCTION_CALL_OPERATOR_BY_PERFECT_arg_type(R, _, I, Bit) \
            BOOST_PP_COMMA_IF(I) BOOST_PP_CAT(BOOST_EGG_FUNCTION_CALL_OPERATOR_BY_PERFECT_ac, Bit)(BOOST_PP_CAT(A, I)) \
        /**/

        #define BOOST_EGG_FUNCTION_CALL_OPERATOR_BY_PERFECT_param(R, _, I, Bit) \
            BOOST_PP_COMMA_IF(I) BOOST_PP_CAT(A, I) BOOST_PP_CAT(BOOST_EGG_FUNCTION_CALL_OPERATOR_BY_PERFECT_c, Bit) & BOOST_PP_CAT(a, I) \
        /**/

        #define BOOST_EGG_FUNCTION_CALL_OPERATOR_BY_PERFECT_c0
        #define BOOST_EGG_FUNCTION_CALL_OPERATOR_BY_PERFECT_c1 const

        #define BOOST_EGG_FUNCTION_CALL_OPERATOR_BY_PERFECT_ac0(A) A
        #define BOOST_EGG_FUNCTION_CALL_OPERATOR_BY_PERFECT_ac1(A) BOOST_EGG_DEDUCED_CONST(A)


#endif // defined(BOOST_EGG_HAS_RVALUE_REFS)


#endif
