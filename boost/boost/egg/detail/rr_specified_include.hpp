#ifndef BOOST_PP_IS_ITERATING


// Boost.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#if !defined(BOOST_EGG_SPECIFIED_PARAMS)
    #error Please define BOOST_EGG_SPECIFIED_PARAMS.
#endif
#define BOOST_EGG_name    BOOST_PP_TUPLE_ELEM(4, 0, BOOST_EGG_SPECIFIED_PARAMS)
#define BOOST_EGG_op      BOOST_PP_TUPLE_ELEM(4, 1, BOOST_EGG_SPECIFIED_PARAMS)
#define BOOST_EGG_params  BOOST_EGG_PP_TO_TEMPLATE_PARAM_SEQ(BOOST_PP_TUPLE_ELEM(4, 2, BOOST_EGG_SPECIFIED_PARAMS))
#define BOOST_EGG_arities BOOST_PP_SEQ_TO_ARRAY(BOOST_PP_TUPLE_ELEM(4, 3, BOOST_EGG_SPECIFIED_PARAMS))


    #define BOOST_EGG_forward(Z, N, A) boost::egg::std_forward<BOOST_PP_CAT(A, N)>(BOOST_PP_CAT(a, N))
        #define  BOOST_EGG_PP_ARRAY_ITERATION_PARAMS (BOOST_EGG_arities, <boost/egg/detail/rr_specified_include.hpp>)
        #include BOOST_EGG_PP_ARRAY_ITERATE()
    #undef  BOOST_EGG_forward


#undef  BOOST_EGG_arities
#undef  BOOST_EGG_params
#undef  BOOST_EGG_op
#undef  BOOST_EGG_name
#undef  BOOST_EGG_SPECIFIED_PARAMS


#else
#define n BOOST_EGG_PP_ARRAY_ITERATION()


    template<BOOST_EGG_PP_SEQ_ENUM_PARAMS(BOOST_EGG_params, X) BOOST_PP_ENUM_TRAILING_PARAMS(n, class A)> inline
    typename result_of<BOOST_EGG_op<BOOST_EGG_PP_SEQ_ENUM_ARGS(BOOST_EGG_params, X)>(
        BOOST_PP_ENUM_PARAMS(n, A)
    )>::type
    BOOST_EGG_name(BOOST_PP_ENUM_BINARY_PARAMS(n, A, &&a))
    {
        return BOOST_EGG_op<BOOST_EGG_PP_SEQ_ENUM_ARGS(BOOST_EGG_params, X)>()(
            BOOST_PP_ENUM(n, BOOST_EGG_forward, A)
        );
    }


#undef  n
#endif
