

// PStade.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#if !defined(PSTADE_PP_ARRAY_ITERATION_PARAMS)
    #error Please define PSTADE_PP_ARRAY_ITERATION_PARAMS.
#endif
#define PSTADE_PP_ARRAY_ITERATION_array BOOST_PP_TUPLE_ELEM(2, 0, PSTADE_PP_ARRAY_ITERATION_PARAMS)
#define PSTADE_PP_ARRAY_ITERATION_file  BOOST_PP_TUPLE_ELEM(2, 1, PSTADE_PP_ARRAY_ITERATION_PARAMS)


    #define  BOOST_PP_ITERATION_PARAMS_1 (3, (0, BOOST_PP_DEC(BOOST_PP_ARRAY_SIZE(PSTADE_PP_ARRAY_ITERATION_array)), PSTADE_PP_ARRAY_ITERATION_file))
    #include BOOST_PP_ITERATE()


#undef  PSTADE_PP_ARRAY_ITERATION_file
#undef  PSTADE_PP_ARRAY_ITERATION_array
#undef  PSTADE_PP_ARRAY_ITERATION_PARAMS
