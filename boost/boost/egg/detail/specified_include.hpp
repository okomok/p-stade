#ifndef BOOST_PP_IS_ITERATING


// Boost.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// See: <boost/detail/function_n.hpp>
//
// Copyright David Abrahams 2006. Distributed under the Boost
// Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)


#if !defined(BOOST_EGG_SPECIFIED_PARAMS)
    #error Please define BOOST_EGG_SPECIFIED_PARAMS.
#endif
#define BOOST_EGG_name    BOOST_PP_TUPLE_ELEM(4, 0, BOOST_EGG_SPECIFIED_PARAMS)
#define BOOST_EGG_op      BOOST_PP_TUPLE_ELEM(4, 1, BOOST_EGG_SPECIFIED_PARAMS)
#define BOOST_EGG_params  BOOST_EGG_PP_TO_TEMPLATE_PARAM_SEQ(BOOST_PP_TUPLE_ELEM(4, 2, BOOST_EGG_SPECIFIED_PARAMS))
#define BOOST_EGG_arities BOOST_PP_SEQ_TO_ARRAY(BOOST_PP_TUPLE_ELEM(4, 3, BOOST_EGG_SPECIFIED_PARAMS))


    #define BOOST_EGG_function(R, BitSeq) \
        BOOST_EGG_function_aux( \
            BOOST_PP_SEQ_FOR_EACH_I_R(R, BOOST_EGG_arg_type, ~, BitSeq), \
            BOOST_PP_SEQ_FOR_EACH_I_R(R, BOOST_EGG_param,    ~, BitSeq), \
            BOOST_PP_SEQ_SIZE(BitSeq) \
        ) \
    /**/
    #define BOOST_EGG_function_aux(ArgTypes, Params, N) \
        template<BOOST_EGG_PP_SEQ_ENUM_PARAMS(BOOST_EGG_params, X), BOOST_PP_ENUM_PARAMS(N, class A)> inline \
        BOOST_EGG_RESULT_OF_IN_NS_SCOPE( (BOOST_EGG_op<BOOST_EGG_PP_SEQ_ENUM_ARGS(BOOST_EGG_params, X)>), ArgTypes ) \
        BOOST_EGG_name( Params BOOST_EGG_CONST_OVERLOADED_SEQ(BOOST_EGG_PP_SEQ_PARAMS(N, A)) ) \
        { \
            return BOOST_EGG_op<BOOST_EGG_PP_SEQ_ENUM_ARGS(BOOST_EGG_params, X)>()(BOOST_PP_ENUM_PARAMS(N, a)); \
        } \
    /**/
    #define BOOST_EGG_arg_type(R, _, I, Bit) ( BOOST_PP_CAT(BOOST_EGG_ac, Bit)(BOOST_PP_CAT(A, I)) )
    #define BOOST_EGG_param(R, _, I, Bit) BOOST_PP_COMMA_IF(I) BOOST_PP_CAT(A, I) BOOST_PP_CAT(BOOST_EGG_c, Bit) & BOOST_PP_CAT(a, I)
    #define BOOST_EGG_c0
    #define BOOST_EGG_c1 const
    #define BOOST_EGG_ac0(A) A &
    #define BOOST_EGG_ac1(A) BOOST_EGG_CONST_REF(A)
        #define  BOOST_EGG_PP_ARRAY_ITERATION_PARAMS (BOOST_EGG_arities, <boost/egg/detail/specified_include.hpp>)
        #include BOOST_EGG_PP_ARRAY_ITERATE()
    #undef  BOOST_EGG_ac1
    #undef  BOOST_EGG_ac0
    #undef  BOOST_EGG_c1
    #undef  BOOST_EGG_c0
    #undef  BOOST_EGG_param
    #undef  BOOST_EGG_arg_type
    #undef  BOOST_EGG_function_aux
    #undef  BOOST_EGG_function


#undef  BOOST_EGG_arities
#undef  BOOST_EGG_params
#undef  BOOST_EGG_op
#undef  BOOST_EGG_name
#undef  BOOST_EGG_SPECIFIED_PARAMS


#else
#define n BOOST_EGG_PP_ARRAY_ITERATION()


#if n == 0

    template<BOOST_EGG_PP_SEQ_ENUM_PARAMS(BOOST_EGG_params, X)> inline
    typename boost::egg::result_of_<BOOST_EGG_op<BOOST_EGG_PP_SEQ_ENUM_ARGS(BOOST_EGG_params, X)>()>::type
    BOOST_EGG_name()
    {
        return BOOST_EGG_op<BOOST_EGG_PP_SEQ_ENUM_ARGS(BOOST_EGG_params, X)>()();
    }

#else

    BOOST_PP_SEQ_FOR_EACH_PRODUCT(BOOST_EGG_function, BOOST_EGG_PP_SEQ_REPEAT((0)(1), n))

#endif


#undef  n
#endif
