

// PStade.Wine
//
// Copyright Shunsuke Sogame 2005-2007.
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


// Usage:
//
// #include <pstade/cast_function.hpp> // Don't forget.
// namespace my {
//     template<class T> struct op_my_cast { .. };
//     #define PSTADE_CAST_FUNCTION_PARAMS ((1)(3), my_cast, op_my_cast, (class))
//     #include <pstade/cast_function.hpp>
// }
//
// 5 or more arity is not recommended; it tends to make so many functions.


#if !defined(PSTADE_CAST_FUNCTION_PARAMS)


    #ifndef PSTADE_CAST_FUNCTION_HEADER_PART
    #define PSTADE_CAST_FUNCTION_HEADER_PART


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
    #include <pstade/deduced_const.hpp>
    #include <pstade/preprocessor.hpp>


    // Prefer these in the case of small arity.


    #define PSTADE_CAST_FUNCTION0(Name, Op, SeqOrNum) \
        PSTADE_CAST_FUNCTION0_aux(Name, Op, PSTADE_PP_TO_TEMPLATE_PARAM_SEQ(SeqOrNum)) \
    /**/

        #define PSTADE_CAST_FUNCTION0_aux(Name, Op, Seq) \
            template<PSTADE_PP_TO_TEMPLATE_PARAMS(Seq, X)> inline \
            typename ::boost::result_of<Op<PSTADE_PP_TO_TEMPLATE_ARGS(Seq, X)>()>::type \
            Name() \
            { \
                return Op<PSTADE_PP_TO_TEMPLATE_ARGS(Seq, X)>()(); \
            }
        /**/


    #define PSTADE_CAST_FUNCTION1(Name, Op, SeqOrNum) \
        PSTADE_CAST_FUNCTION1_aux(Name, Op, PSTADE_PP_TO_TEMPLATE_PARAM_SEQ(SeqOrNum)) \
    /**/

        #define PSTADE_CAST_FUNCTION1_aux(Name, Op, Seq) \
            template<PSTADE_PP_TO_TEMPLATE_PARAMS(Seq, X), class A0> inline \
            typename ::boost::result_of<Op<PSTADE_PP_TO_TEMPLATE_ARGS(Seq, X)>(A0&)>::type \
            Name(A0& a0 PSTADE_CONST_OVERLOADED(A0)) \
            { \
                return Op<PSTADE_PP_TO_TEMPLATE_ARGS(Seq, X)>()(a0); \
            } \
            \
            template<PSTADE_PP_TO_TEMPLATE_PARAMS(Seq, X), class A0> inline \
            typename ::boost::result_of<Op<PSTADE_PP_TO_TEMPLATE_ARGS(Seq, X)>(PSTADE_DEDUCED_CONST(A0)&)>::type \
            Name(A0 const& a0) \
            { \
                return Op<PSTADE_PP_TO_TEMPLATE_ARGS(Seq, X)>()(a0); \
            } \
        /**/


    #endif // PSTADE_CAST_FUNCTION_HEADER_PART


#else // !defined(PSTADE_CAST_FUNCTION_PARAMS)


    #define PSTADE_args BOOST_PP_TUPLE_ELEM(4, 0, PSTADE_CAST_FUNCTION_PARAMS)
    #define PSTADE_name BOOST_PP_TUPLE_ELEM(4, 1, PSTADE_CAST_FUNCTION_PARAMS)
    #define PSTADE_op   BOOST_PP_TUPLE_ELEM(4, 2, PSTADE_CAST_FUNCTION_PARAMS)
    #define PSTADE_classes PSTADE_PP_TO_TEMPLATE_PARAM_SEQ(BOOST_PP_TUPLE_ELEM(4, 3, PSTADE_CAST_FUNCTION_PARAMS))


    #define PSTADE_call_operator(R, BitSeq) \
        PSTADE_call_operator_aux( \
            BOOST_PP_SEQ_FOR_EACH_I_R(R, PSTADE_arg_type, ~, BitSeq), \
            BOOST_PP_SEQ_FOR_EACH_I_R(R, PSTADE_param,    ~, BitSeq), \
            BOOST_PP_SEQ_SIZE(BitSeq) \
        ) \
    /**/
    #define PSTADE_call_operator_aux(ArgTypes, Params, N) \
        template<PSTADE_PP_TO_TEMPLATE_PARAMS(PSTADE_classes, X), BOOST_PP_ENUM_PARAMS(N, class A)> inline \
        typename ::boost::result_of< PSTADE_op<PSTADE_PP_TO_TEMPLATE_ARGS(PSTADE_classes, X)>(ArgTypes) >::type \
        PSTADE_name( Params PSTADE_CONST_OVERLOADED_SEQ(PSTADE_PP_SEQ_PARAMS(N, A)) ) \
        { \
            return PSTADE_op<PSTADE_PP_TO_TEMPLATE_ARGS(PSTADE_classes, X)>()(BOOST_PP_ENUM_PARAMS(N, a)); \
        } \
    /**/
    #define PSTADE_arg_type(R, _, I, Bit) BOOST_PP_COMMA_IF(I) BOOST_PP_CAT(PSTADE_ac, Bit)(BOOST_PP_CAT(A, I)) &
    #define PSTADE_param(R, _, I, Bit)    BOOST_PP_COMMA_IF(I) BOOST_PP_CAT(A, I) BOOST_PP_CAT(PSTADE_c, Bit) & BOOST_PP_CAT(a, I)
    #define PSTADE_c0
    #define PSTADE_c1 const
    #define PSTADE_ac0(A) A
    #define PSTADE_ac1(A) PSTADE_DEDUCED_CONST(A)

    #define PSTADE_gen_operator0(R, N) PSTADE_CAST_FUNCTION0_aux(PSTADE_name, PSTADE_op, PSTADE_classes)
    #define PSTADE_gen_operatorN(R, N) BOOST_PP_SEQ_FOR_EACH_PRODUCT_R(R, PSTADE_call_operator, PSTADE_PP_SEQ_REPEAT((0)(1), N))
    #define PSTADE_gen_operator(R, _, N)  BOOST_PP_IF(N, PSTADE_gen_operatorN, PSTADE_gen_operator0)(R, N)
        BOOST_PP_SEQ_FOR_EACH(PSTADE_gen_operator, ~, PSTADE_args)
    #undef  PSTADE_gen_operator
    #undef  PSTADE_gen_operatorN
    #undef  PSTADE_gen_operator0

    #undef  PSTADE_ac1
    #undef  PSTADE_ac0
    #undef  PSTADE_c1
    #undef  PSTADE_c0
    #undef  PSTADE_param
    #undef  PSTADE_arg_type
    #undef  PSTADE_call_operator_aux
    #undef  PSTADE_call_operator


    #undef  PSTADE_classes
    #undef  PSTADE_op
    #undef  PSTADE_args
    #undef  PSTADE_name


    #undef  PSTADE_CAST_FUNCTION_PARAMS


#endif // !defined(PSTADE_CAST_FUNCTION_PARAMS)
