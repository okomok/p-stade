#ifndef BOOST_PP_IS_ITERATING
#ifndef PSTADE_PROVIDE_SIG_HPP
#define PSTADE_PROVIDE_SIG_HPP
#include "./detail/prefix.hpp"


// PStade.Wine
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// Copyright 2005 Cryolite.
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/mpl/int.hpp>
#include <boost/preprocessor/iteration/iterate.hpp>
#include <boost/preprocessor/repetition/enum.hpp>
#include <boost/tuple/tuple.hpp>
#include <boost/utility/result_of.hpp>
#include <pstade/adl_barrier.hpp>


#if !defined(PSTADE_PROVIDE_SIG_MAX_ARITY)
    #define PSTADE_PROVIDE_SIG_MAX_ARITY 10 // follows 'tuple'.
#endif


namespace pstade {


PSTADE_ADL_BARRIER(provide_sig) {


    struct provide_sig
    {
    private:
        template<class Fun, class Args, class Arity>
        struct sig_aux;

        // 0ary
        template<class Fun, class Args>
        struct sig_aux< Fun, Args, boost::mpl::int_<0> > :
            boost::result_of<
                Fun()
            >
        { };

        // 1ary-
    #define PSTADE_element(Z, N, _) typename boost::tuples::element<N, Args>::type &
        #define  BOOST_PP_ITERATION_PARAMS_1 (3, (1, PSTADE_PROVIDE_SIG_MAX_ARITY, <pstade/provide_sig.hpp>))
        #include BOOST_PP_ITERATE()
    #undef  PSTADE_element

    public:
        template<class SigArgs>
        struct sig :
            sig_aux<
                typename SigArgs::head_type, // function
                typename SigArgs::tail_type, // argument tuple
                boost::mpl::int_<boost::tuples::length<SigArgs>::value - 1>
            >
        { };
    };


} // ADL barrier


} // namespace pstade


#endif
#else
#define n BOOST_PP_ITERATION()


template<class Fun, class Args>
struct sig_aux< Fun, Args, boost::mpl::int_<n> > :
    boost::result_of<
        Fun(BOOST_PP_ENUM(n, PSTADE_element, ~))
    >
{ };


#undef n
#endif
