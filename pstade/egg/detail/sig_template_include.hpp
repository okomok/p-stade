#ifndef BOOST_PP_IS_ITERATING


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


    template<class Fun, class Args, class Arity>
    struct sig_aux;

    // 0ary
    template<class Fun, class Args>
    struct sig_aux< Fun, Args, boost::mpl::int_<0> > :
        pstade::result_of<
            Fun()
        >
    { };

    // 1ary-
#define PSTADE_element(Z, N, _) typename boost::tuples::element<N, Args>::type &
    #define  BOOST_PP_ITERATION_PARAMS_1 (3, (1, PSTADE_EGG_BLL_BIND_TARGET_MAX_ARITY, <pstade/egg/detail/sig_template_include.hpp>))
    #include BOOST_PP_ITERATE()
#undef  PSTADE_element

    template<class SigArgs>
    struct sig :
        sig_aux<
            typename SigArgs::head_type, // function
            typename SigArgs::tail_type, // argument tuple
            boost::mpl::int_<boost::tuples::length<SigArgs>::value - 1>
        >
    { };


#else
#define n BOOST_PP_ITERATION()


    template<class Fun, class Args>
    struct sig_aux< Fun, Args, boost::mpl::int_<n> > :
        pstade::result_of<
            Fun(BOOST_PP_ENUM(n, PSTADE_element, ~))
        >
    { };


#undef n
#endif
