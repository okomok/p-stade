#ifndef BOOST_PP_IS_ITERATING


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#if !defined(PSTADE_EGG_SPECIFIED_PARAMS)
    #error Please define PSTADE_EGG_SPECIFIED_PARAMS.
#endif
#define PSTADE_name    BOOST_PP_TUPLE_ELEM(4, 0, PSTADE_EGG_SPECIFIED_PARAMS)
#define PSTADE_op      BOOST_PP_TUPLE_ELEM(4, 1, PSTADE_EGG_SPECIFIED_PARAMS)
#define PSTADE_params  PSTADE_PP_TO_TEMPLATE_PARAM_SEQ(BOOST_PP_TUPLE_ELEM(4, 2, PSTADE_EGG_SPECIFIED_PARAMS))
#define PSTADE_arities BOOST_PP_SEQ_TO_ARRAY(BOOST_PP_TUPLE_ELEM(4, 3, PSTADE_EGG_SPECIFIED_PARAMS))


    #define PSTADE_forward(Z, N, A) pstade::egg::std_forward<BOOST_PP_CAT(A, N)>(BOOST_PP_CAT(a, N))
        #define  BOOST_PP_ITERATION_PARAMS_1 (3, (0, BOOST_PP_DEC(BOOST_PP_ARRAY_SIZE(PSTADE_arities)), <pstade/egg/detail/rr_specified_include.hpp>))
        #include BOOST_PP_ITERATE()
    #undef  PSTADE_forward


#undef  PSTADE_arities
#undef  PSTADE_params
#undef  PSTADE_op
#undef  PSTADE_name
#undef  PSTADE_EGG_SPECIFIED_PARAMS


#else
#define n BOOST_PP_ARRAY_ELEM(BOOST_PP_ITERATION(), PSTADE_arities)


    template<PSTADE_PP_SEQ_ENUM_PARAMS(PSTADE_params, X) BOOST_PP_ENUM_TRAILING_PARAMS(n, class A)> inline
    typename result_of<PSTADE_op<PSTADE_PP_SEQ_ENUM_ARGS(PSTADE_params, X)>(
        BOOST_PP_ENUM_PARAMS(n, A)
    )>::type
    PSTADE_name(BOOST_PP_ENUM_BINARY_PARAMS(n, A, && a))
    {
        return PSTADE_op<PSTADE_PP_SEQ_ENUM_ARGS(PSTADE_params, X)>()(
            BOOST_PP_ENUM(n, PSTADE_forward, A)
        );
    }


#undef  n
#endif
