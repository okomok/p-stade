#ifndef BOOST_PP_IS_ITERATING
#ifndef PSTADE_EGG_BLL_SIG_HPP
#define PSTADE_EGG_BLL_SIG_HPP


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// Usage:
//
// template<class FunArgs>
// struct sig : bll_sig<FunArgs> {};


#include <boost/mpl/int.hpp>
#include <boost/preprocessor/iteration/iterate.hpp>
#include <boost/preprocessor/repetition/enum.hpp>
#include <boost/tuple/tuple.hpp>
#include <pstade/result_of.hpp>
#include "./bll/config.hpp" // PSTADE_EGG_BLL_BIND_TARGET_MAX_ARITY


namespace pstade { namespace egg {


    namespace bll_sig_detail {


        template<class Fun, class Args, class Arity>
        struct aux_;

    #define PSTADE_element(Z, N, _) typename boost::tuples::element<N, Args>::type &
        #define  BOOST_PP_ITERATION_PARAMS_1 (3, (0, PSTADE_EGG_BLL_BIND_TARGET_MAX_ARITY, <pstade/egg/bll_sig.hpp>))
        #include BOOST_PP_ITERATE()
    #undef  PSTADE_element


    } // namespace bll_sig_detail


    template<class FunArgs>
    struct bll_sig :
        bll_sig_detail::aux_<
            typename FunArgs::head_type, // function
            typename FunArgs::tail_type, // argument tuple
            boost::mpl::int_<boost::tuples::length<FunArgs>::value - 1>
        >
    { };


} } // namespace pstade::egg


#endif
#else
#define n BOOST_PP_ITERATION()


    template<class Fun, class Args>
    struct aux_< Fun, Args, boost::mpl::int_<n> > :
        result_of<
            Fun(BOOST_PP_ENUM(n, PSTADE_element, ~))
        >
    { };


#undef  n
#endif
