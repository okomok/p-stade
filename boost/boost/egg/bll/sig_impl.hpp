#ifndef BOOST_PP_IS_ITERATING
#ifndef BOOST_EGG_BLL_SIG_IMPL_HPP
#define BOOST_EGG_BLL_SIG_IMPL_HPP


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// Usage:
//
// template<class FunArgs>
// struct sig : bll_sig_impl<FunArgs> {};


#include <boost/mpl/int.hpp>
#include <boost/preprocessor/iteration/iterate.hpp>
#include <boost/preprocessor/repetition/enum.hpp>
#include <boost/tuple/tuple.hpp>
#include <boost/egg/result_of.hpp>
#include <boost/egg/bll/config.hpp> // BOOST_EGG_BLL_BIND_TARGET_MAX_ARITY


namespace boost { namespace egg {


    namespace bll_sig_impl_detail {


        template<class Fun, class Args, class Arity>
        struct aux_;

    #define PSTADE_element(Z, N, _) typename tuples::element<N, Args>::type &
        #define  BOOST_PP_ITERATION_PARAMS_1 (3, (0, BOOST_EGG_BLL_BIND_TARGET_MAX_ARITY, <boost/egg/bll/sig_impl.hpp>))
        #include BOOST_PP_ITERATE()
    #undef  PSTADE_element


    } // namespace bll_sig_impl_detail


    template<class FunArgs>
    struct bll_sig_impl :
        bll_sig_impl_detail::aux_<
            typename FunArgs::head_type, // function
            typename FunArgs::tail_type, // argument tuple
            mpl::int_<tuples::length<FunArgs>::value - 1>
        >
    { };


} } // namespace boost::egg


#endif
#else
#define n BOOST_PP_ITERATION()


    template<class Fun, class Args>
    struct aux_< Fun, Args, mpl::int_<n> > :
        result_of<
            Fun(BOOST_PP_ENUM(n, PSTADE_element, ~))
        >
    { };


#undef  n
#endif
