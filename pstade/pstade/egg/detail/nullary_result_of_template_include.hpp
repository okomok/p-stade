

// PStade.Egg
//
// Copyright Shunsuke Sogame 2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#if !defined(PSTADE_EGG_NULLARY_RESULT_OF_TEMPLATE_PARAMS)
    #error Please define PSTADE_EGG_NULLARY_RESULT_OF_TEMPLATE_PARAMS.
#endif
#define PSTADE_name BOOST_PP_TUPLE_ELEM(2, 0, PSTADE_EGG_NULLARY_RESULT_OF_TEMPLATE_PARAMS)
#define PSTADE_seq  PSTADE_PP_TO_TEMPLATE_PARAM_SEQ(BOOST_PP_TUPLE_ELEM(2, 1, PSTADE_EGG_NULLARY_RESULT_OF_TEMPLATE_PARAMS))


    namespace boost {

        template<PSTADE_PP_SEQ_ENUM_PARAMS(PSTADE_seq, T)>
        struct result_of< PSTADE_name<PSTADE_PP_SEQ_ENUM_ARGS(PSTADE_seq, T)>(void) >
        {
            typedef typename PSTADE_name<PSTADE_PP_SEQ_ENUM_ARGS(PSTADE_seq, T)>::nullary_result_type type;
        };

        template<PSTADE_PP_SEQ_ENUM_PARAMS(PSTADE_seq, T)>
        struct result_of< PSTADE_name<PSTADE_PP_SEQ_ENUM_ARGS(PSTADE_seq, T)> const(void) > :
               result_of< PSTADE_name<PSTADE_PP_SEQ_ENUM_ARGS(PSTADE_seq, T)>() >
        { };

     }


#undef  PSTADE_seq
#undef  PSTADE_name
#undef  PSTADE_EGG_NULLARY_RESULT_OF_TEMPLATE_PARAMS
