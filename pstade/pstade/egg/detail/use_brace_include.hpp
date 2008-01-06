#ifndef BOOST_PP_IS_ITERATING


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#if !defined(PSTADE_EGG_USE_BRACE_N)
    #error Please define PSTADE_EGG_USE_BRACE_N.
#endif


    struct BOOST_PP_CAT(use_brace, PSTADE_EGG_USE_BRACE_N)
    {
    // 0ary
        template<class X>
        X operator()(boost::type<X>) const
        {
            X x = PSTADE_EGG_REPEAT_BRACE_L(PSTADE_EGG_USE_BRACE_N) PSTADE_EGG_REPEAT_BRACE_R(PSTADE_EGG_USE_BRACE_N);
            return x;
        }

    // 1ary-
        #define  BOOST_PP_ITERATION_PARAMS_1 (3, (1, BOOST_MPL_LIMIT_METAFUNCTION_ARITY, <pstade/egg/detail/use_brace_include.hpp>))
        #include BOOST_PP_ITERATE()
    };


#undef  PSTADE_EGG_USE_BRACE_N


#else
#define n BOOST_PP_ITERATION()


    template<class X, BOOST_PP_ENUM_PARAMS(n, class A)>
    X operator()(boost::type<X>, BOOST_PP_ENUM_BINARY_PARAMS(n, A, & a)) const
    {
        X x = PSTADE_EGG_REPEAT_BRACE_L(PSTADE_EGG_USE_BRACE_N) BOOST_PP_ENUM_PARAMS(n, a) PSTADE_EGG_REPEAT_BRACE_R(PSTADE_EGG_USE_BRACE_N);
        return x;
    }


#undef n
#endif
