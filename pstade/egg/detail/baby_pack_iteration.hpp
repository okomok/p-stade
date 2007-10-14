#ifndef BOOST_PP_IS_ITERATING


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#ifndef PSTADE_EGG_DETAIL_PACK_TEMPLATE
    #error Please define PSTADE_EGG_DETAIL_PACK_TEMPLATE(N).
#endif
#ifndef PSTADE_EGG_DETAIL_PACK_MAX_ARITY
    #error Please define PSTADE_EGG_DETAIL_PACK_MAX_ARITY.
#endif


    struct baby_pack
    {
    // 0ary
        typedef PSTADE_EGG_DETAIL_PACK_TEMPLATE(0)<> nullary_result_type;

        template<class Result>
        Result call() const
        {
            return Result();
        }

    // 1ary-
        template<class Myself, PSTADE_EGG_APPLY_PARAMS(PSTADE_EGG_DETAIL_PACK_MAX_ARITY, A)>
        struct apply { }; // msvc warns if incomplete.

        #define  BOOST_PP_ITERATION_PARAMS_1 (3, (1, PSTADE_EGG_DETAIL_PACK_MAX_ARITY, <pstade/egg/detail/baby_pack_iteration.hpp>))
        #include BOOST_PP_ITERATE()
    };


#undef  PSTADE_EGG_DETAIL_PACK_TEMPLATE
#undef  PSTADE_EGG_DETAIL_PACK_MAX_ARITY


#else
#define n BOOST_PP_ITERATION()


    template<class Myself, BOOST_PP_ENUM_PARAMS(n, class A)>
    struct apply<Myself, BOOST_PP_ENUM_PARAMS(n, A)>
    {
        typedef PSTADE_EGG_DETAIL_PACK_TEMPLATE(n)<PSTADE_PP_ENUM_PARAMS_WITH(n, A, &)> type;
    };

    template<class Result, BOOST_PP_ENUM_PARAMS(n, class A)>
    Result call(BOOST_PP_ENUM_BINARY_PARAMS(n, A, & a)) const
    {
        return Result(BOOST_PP_ENUM_PARAMS(n, a));
    }


#undef n
#endif