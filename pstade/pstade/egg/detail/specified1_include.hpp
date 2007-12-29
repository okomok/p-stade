

// PStade.Egg
//
// Copyright Shunsuke Sogame 2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#if !defined(PSTADE_EGG_SPECIFIED1_PARAMS)
    #error Please define PSTADE_EGG_SPECIFIED1_PARAMS.
#endif
#define PSTADE_name    BOOST_PP_TUPLE_ELEM(3, 0, PSTADE_EGG_SPECIFIED1_PARAMS)
#define PSTADE_op      BOOST_PP_TUPLE_ELEM(3, 1, PSTADE_EGG_SPECIFIED1_PARAMS)
#define PSTADE_params  PSTADE_PP_TO_TEMPLATE_PARAM_SEQ(BOOST_PP_TUPLE_ELEM(3, 2, PSTADE_EGG_SPECIFIED1_PARAMS))


    template<PSTADE_PP_SEQ_ENUM_PARAMS(PSTADE_params, X), class A0> inline
    PSTADE_EGG_RESULT_OF_IN_NS_SCOPE((PSTADE_op<PSTADE_PP_SEQ_ENUM_ARGS(PSTADE_params, X)>), (A0&))
    PSTADE_name(A0& a0 PSTADE_CONST_OVERLOADED(A0))
    {
        return PSTADE_op<PSTADE_PP_SEQ_ENUM_ARGS(PSTADE_params, X)>()(a0);
    }

    template<PSTADE_PP_SEQ_ENUM_PARAMS(PSTADE_params, X), class A0> inline
    PSTADE_EGG_RESULT_OF_IN_NS_SCOPE((PSTADE_op<PSTADE_PP_SEQ_ENUM_ARGS(PSTADE_params, X)>), (PSTADE_EGG_CONST_REF(A0)))
    PSTADE_name(A0 const& a0)
    {
        return PSTADE_op<PSTADE_PP_SEQ_ENUM_ARGS(PSTADE_params, X)>()(a0);
    }


#undef  PSTADE_params
#undef  PSTADE_op
#undef  PSTADE_name
#undef  PSTADE_EGG_SPECIFIED1_PARAMS
