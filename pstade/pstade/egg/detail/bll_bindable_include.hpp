#ifndef BOOST_PP_IS_ITERATING


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


    template<class Egg_Fun, class Egg_Args, class Egg_Arity>
    struct sig_aux;

    // 0ary
    template<class Egg_Fun, class Egg_Args>
    struct sig_aux< Egg_Fun, Egg_Args, boost::mpl::int_<0> > :
        pstade::result_of<
            Egg_Fun()
        >
    { };

    // 1ary-
#define PSTADE_element(Z, N, _) typename boost::tuples::element<N, Egg_Args>::type &
    #define  BOOST_PP_ITERATION_PARAMS_1 (3, (1, PSTADE_EGG_BLL_BIND_TARGET_MAX_ARITY, <pstade/egg/detail/bll_bindable_include.hpp>))
    #include BOOST_PP_ITERATE()
#undef  PSTADE_element

    template<class Egg_SigArgs>
    struct sig :
        sig_aux<
            typename Egg_SigArgs::head_type, // function
            typename Egg_SigArgs::tail_type, // argument tuple
            boost::mpl::int_<boost::tuples::length<Egg_SigArgs>::value - 1>
        >
    { };


#else


    template<class Egg_Fun, class Egg_Args>
    struct sig_aux< Egg_Fun, Egg_Args, boost::mpl::int_<BOOST_PP_ITERATION()> > :
        pstade::result_of<
            Egg_Fun(BOOST_PP_ENUM(BOOST_PP_ITERATION(), PSTADE_element, ~))
        >
    { };


#endif
