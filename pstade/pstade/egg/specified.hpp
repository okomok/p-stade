#include "./detail/prefix.hpp"


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// See: <boost/detail/function_n.hpp>
//
// Copyright David Abrahams 2006. Distributed under the Boost
// Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)


// What:
//
// Does perfect forwarding for cast form functions.
// The "result_of revolution" turns a namespace scope function
// into nothing but a syntax sugar, though.


// Usage:
//
// namespace my {
//     template<class T> struct op_my_cast { .. };
//     #define  PSTADE_EGG_SPECIFIED_PARAMS ((1)(3), my_cast, op_my_cast, (class))
//     #include PSTADE_EGG_SPECIFIED()
// }
//
// 5 or more arity is not recommended; it tends to make so many functions.


#if !defined(PSTADE_EGG_SPECIFIED_PARAMS)


    #ifndef PSTADE_EGG_SPECIFIED_HEADER_PART
    #define PSTADE_EGG_SPECIFIED_HEADER_PART


    #include <boost/config.hpp>
    #include <boost/detail/workaround.hpp>
    #include <boost/preprocessor/cat.hpp>
    #include <boost/preprocessor/control/if.hpp>
    #include <boost/preprocessor/iteration/iterate.hpp>
    #include <boost/preprocessor/punctuation/comma_if.hpp>
    #include <boost/preprocessor/seq/for_each.hpp>
    #include <boost/preprocessor/seq/for_each_i.hpp>
    #include <boost/preprocessor/seq/for_each_product.hpp>
    #include <boost/preprocessor/seq/size.hpp>
    #include <boost/preprocessor/tuple/elem.hpp>
    #include <boost/utility/result_of.hpp>
    #include <pstade/const_overloaded.hpp>
    #include <pstade/preprocessor.hpp>
    #include "./detail/result_of.hpp"


    #define PSTADE_EGG_SPECIFIED() <pstade/egg/specified.hpp>


    // Prefer these in the case of small arity.


    #define PSTADE_EGG_SPECIFIED0(Name, Op, SeqOrNum) \
        PSTADE_EGG_SPECIFIED0_aux(Name, Op, PSTADE_PP_TO_TEMPLATE_PARAM_SEQ(SeqOrNum)) \
    /**/

        #define PSTADE_EGG_SPECIFIED0_aux(Name, Op, Seq) \
            template<PSTADE_PP_TO_TEMPLATE_PARAMS(Seq, X)> inline \
            typename boost::result_of<Op<PSTADE_PP_TO_TEMPLATE_ARGS(Seq, X)>()>::type \
            Name() \
            { \
                return Op<PSTADE_PP_TO_TEMPLATE_ARGS(Seq, X)>()(); \
            }
        /**/


    #define PSTADE_EGG_SPECIFIED1(Name, Op, SeqOrNum) \
        PSTADE_EGG_SPECIFIED1_aux(Name, Op, PSTADE_PP_TO_TEMPLATE_PARAM_SEQ(SeqOrNum)) \
    /**/

        #define PSTADE_EGG_SPECIFIED1_aux(Name, Op, Seq) \
            template<PSTADE_PP_TO_TEMPLATE_PARAMS(Seq, X), class A0> inline \
            PSTADE_EGG_DETAIL_RESULT_OF((Op<PSTADE_PP_TO_TEMPLATE_ARGS(Seq, X)>), (A0&)) \
            Name(A0& a0 PSTADE_CONST_OVERLOADED(A0)) \
            { \
                return Op<PSTADE_PP_TO_TEMPLATE_ARGS(Seq, X)>()(a0); \
            } \
            \
            template<PSTADE_PP_TO_TEMPLATE_PARAMS(Seq, X), class A0> inline \
            PSTADE_EGG_DETAIL_RESULT_OF((Op<PSTADE_PP_TO_TEMPLATE_ARGS(Seq, X)>), (PSTADE_EGG_DETAIL_CONST_REF(A0))) \
            Name(A0 const& a0) \
            { \
                return Op<PSTADE_PP_TO_TEMPLATE_ARGS(Seq, X)>()(a0); \
            } \
        /**/


    #endif // PSTADE_EGG_SPECIFIED_HEADER_PART


#else // !defined(PSTADE_EGG_SPECIFIED_PARAMS)


    #define PSTADE_arities BOOST_PP_TUPLE_ELEM(4, 0, PSTADE_EGG_SPECIFIED_PARAMS)
    #define PSTADE_name    BOOST_PP_TUPLE_ELEM(4, 1, PSTADE_EGG_SPECIFIED_PARAMS)
    #define PSTADE_op      BOOST_PP_TUPLE_ELEM(4, 2, PSTADE_EGG_SPECIFIED_PARAMS)
    #define PSTADE_params  PSTADE_PP_TO_TEMPLATE_PARAM_SEQ(BOOST_PP_TUPLE_ELEM(4, 3, PSTADE_EGG_SPECIFIED_PARAMS))


    #define PSTADE_function(R, BitSeq) \
        PSTADE_function_aux( \
            BOOST_PP_SEQ_FOR_EACH_I_R(R, PSTADE_arg_type, ~, BitSeq), \
            BOOST_PP_SEQ_FOR_EACH_I_R(R, PSTADE_param,    ~, BitSeq), \
            BOOST_PP_SEQ_SIZE(BitSeq) \
        ) \
    /**/
    #define PSTADE_function_aux(ArgTypes, Params, N) \
        template<PSTADE_PP_TO_TEMPLATE_PARAMS(PSTADE_params, X), BOOST_PP_ENUM_PARAMS(N, class A)> inline \
        PSTADE_EGG_DETAIL_RESULT_OF( (PSTADE_op<PSTADE_PP_TO_TEMPLATE_ARGS(PSTADE_params, X)>), ArgTypes ) \
        PSTADE_name( Params PSTADE_CONST_OVERLOADED_SEQ(PSTADE_PP_SEQ_PARAMS(N, A)) ) \
        { \
            return PSTADE_op<PSTADE_PP_TO_TEMPLATE_ARGS(PSTADE_params, X)>()(BOOST_PP_ENUM_PARAMS(N, a)); \
        } \
    /**/
    #define PSTADE_arg_type(R, _, I, Bit) ( BOOST_PP_CAT(PSTADE_ac, Bit)(BOOST_PP_CAT(A, I)) )
    #define PSTADE_param(R, _, I, Bit) BOOST_PP_COMMA_IF(I) BOOST_PP_CAT(A, I) BOOST_PP_CAT(PSTADE_c, Bit) & BOOST_PP_CAT(a, I)
    #define PSTADE_c0
    #define PSTADE_c1 const
    #define PSTADE_ac0(A) A&
    #define PSTADE_ac1(A) PSTADE_EGG_DETAIL_CONST_REF(A)

    #define PSTADE_gen_function0(R, N) PSTADE_EGG_SPECIFIED0_aux(PSTADE_name, PSTADE_op, PSTADE_params)
    #define PSTADE_gen_functionN(R, N) BOOST_PP_SEQ_FOR_EACH_PRODUCT_R(R, PSTADE_function, PSTADE_PP_SEQ_REPEAT((0)(1), N))
    #define PSTADE_gen_function(R, _, N) BOOST_PP_IF(N, PSTADE_gen_functionN, PSTADE_gen_function0)(R, N)
        BOOST_PP_SEQ_FOR_EACH(PSTADE_gen_function, ~, PSTADE_arities)
    #undef  PSTADE_gen_function
    #undef  PSTADE_gen_functionN
    #undef  PSTADE_gen_function0

    #undef  PSTADE_ac1
    #undef  PSTADE_ac0
    #undef  PSTADE_c1
    #undef  PSTADE_c0
    #undef  PSTADE_param
    #undef  PSTADE_arg_type
    #undef  PSTADE_function_aux
    #undef  PSTADE_function


    #undef  PSTADE_params
    #undef  PSTADE_op
    #undef  PSTADE_arities
    #undef  PSTADE_name


    #undef  PSTADE_EGG_SPECIFIED_PARAMS


#endif // !defined(PSTADE_EGG_SPECIFIED_PARAMS)
