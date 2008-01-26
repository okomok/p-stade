#ifndef BOOST_PP_IS_ITERATING


// PStade.Egg
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


#if !defined(PSTADE_EGG_SPECIFIED_PARAMS)
    #error Please define PSTADE_EGG_SPECIFIED_PARAMS.
#endif
#define PSTADE_name    BOOST_PP_TUPLE_ELEM(4, 0, PSTADE_EGG_SPECIFIED_PARAMS)
#define PSTADE_op      BOOST_PP_TUPLE_ELEM(4, 1, PSTADE_EGG_SPECIFIED_PARAMS)
#define PSTADE_params  PSTADE_PP_TO_TEMPLATE_PARAM_SEQ(BOOST_PP_TUPLE_ELEM(4, 2, PSTADE_EGG_SPECIFIED_PARAMS))
#define PSTADE_arities BOOST_PP_SEQ_TO_ARRAY(BOOST_PP_TUPLE_ELEM(4, 3, PSTADE_EGG_SPECIFIED_PARAMS))


    #define PSTADE_function(R, BitSeq) \
        PSTADE_function_aux( \
            BOOST_PP_SEQ_FOR_EACH_I_R(R, PSTADE_arg_type, ~, BitSeq), \
            BOOST_PP_SEQ_FOR_EACH_I_R(R, PSTADE_param,    ~, BitSeq), \
            BOOST_PP_SEQ_SIZE(BitSeq) \
        ) \
    /**/
    #define PSTADE_function_aux(ArgTypes, Params, N) \
        template<PSTADE_PP_SEQ_ENUM_PARAMS(PSTADE_params, X), BOOST_PP_ENUM_PARAMS(N, class A)> inline \
        PSTADE_EGG_RESULT_OF_IN_NS_SCOPE( (PSTADE_op<PSTADE_PP_SEQ_ENUM_ARGS(PSTADE_params, X)>), ArgTypes ) \
        PSTADE_name( Params PSTADE_CONST_OVERLOADED_SEQ(PSTADE_PP_SEQ_PARAMS(N, A)) ) \
        { \
            return PSTADE_op<PSTADE_PP_SEQ_ENUM_ARGS(PSTADE_params, X)>()(BOOST_PP_ENUM_PARAMS(N, a)); \
        } \
    /**/
    #define PSTADE_arg_type(R, _, I, Bit) ( BOOST_PP_CAT(PSTADE_ac, Bit)(BOOST_PP_CAT(A, I)) )
    #define PSTADE_param(R, _, I, Bit) BOOST_PP_COMMA_IF(I) BOOST_PP_CAT(A, I) BOOST_PP_CAT(PSTADE_c, Bit) & BOOST_PP_CAT(a, I)
    #define PSTADE_c0
    #define PSTADE_c1 const
    #define PSTADE_ac0(A) A&
    #define PSTADE_ac1(A) PSTADE_EGG_CONST_REF(A)
        #define  BOOST_PP_ITERATION_PARAMS_1 (3, (0, BOOST_PP_DEC(BOOST_PP_ARRAY_SIZE(PSTADE_arities)), <pstade/egg/detail/specified_include.hpp>))
        #include BOOST_PP_ITERATE()
    #undef  PSTADE_ac1
    #undef  PSTADE_ac0
    #undef  PSTADE_c1
    #undef  PSTADE_c0
    #undef  PSTADE_param
    #undef  PSTADE_arg_type
    #undef  PSTADE_function_aux
    #undef  PSTADE_function


#undef  PSTADE_arities
#undef  PSTADE_params
#undef  PSTADE_op
#undef  PSTADE_name
#undef  PSTADE_EGG_SPECIFIED_PARAMS


#else
#define n BOOST_PP_ARRAY_ELEM(BOOST_PP_ITERATION(), PSTADE_arities)


#if n == 0

    template<PSTADE_PP_SEQ_ENUM_PARAMS(PSTADE_params, X)> inline
    typename pstade::result_of<PSTADE_op<PSTADE_PP_SEQ_ENUM_ARGS(PSTADE_params, X)>()>::type
    PSTADE_name()
    {
        return PSTADE_op<PSTADE_PP_SEQ_ENUM_ARGS(PSTADE_params, X)>()();
    }

#else

    BOOST_PP_SEQ_FOR_EACH_PRODUCT(PSTADE_function, PSTADE_PP_SEQ_REPEAT((0)(1), n))

#endif


#undef  n
#endif
