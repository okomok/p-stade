#ifndef BOOST_PP_IS_ITERATING
#ifndef PSTADE_LAMBDA_SIG_HPP
#define PSTADE_LAMBDA_SIG_HPP


// PStade.Wine
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// Copyright 2005 Cryolite.
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/preprocessor/iteration/iterate.hpp>
#include <boost/preprocessor/repetition/enum.hpp>
#include <boost/tuple/tuple.hpp>
#include <boost/utility/result_of.hpp>
#include <pstade/adl_barrier.hpp>


namespace pstade {

PSTADE_ADL_BARRIER(lambda_sig) {


struct lambda_sig
{
private:
    template< class F, class Args, int Arity >
    struct sig_impl;

    // 0ary
    template< class F, class Args >
    struct sig_impl< F, Args, 0 > :
        boost::result_of<
            F(
            )
        >
    { };

    // 1ary
    template< class F, class Args >
    struct sig_impl< F, Args, 1 > :
        boost::result_of<
            F(
                typename boost::tuples::element< 0, Args >::type &
            )
        >
    { };

    // 2ary-
#define PSTADE_max_arity 3 // undocumented?
#define PSTADE_element(Z, N, _) typename boost::tuples::element< N, Args >::type &
    #define BOOST_PP_ITERATION_PARAMS_1 (3, (2, PSTADE_max_arity, <pstade/lambda_sig.hpp>))
    #include BOOST_PP_ITERATE()
#undef PSTADE_element
#undef PSTADE_max_arity

public:
    template< class SigArgs >
    struct sig :
        sig_impl<
            typename SigArgs::head_type, // function
            typename SigArgs::tail_type, // argument tuple
            boost::tuples::length< SigArgs >::value - 1
        >
    { };

}; // struct lambda_sig


} // ADL barrier

} // namespace pstade


#endif
#else
#define n BOOST_PP_ITERATION()


    template< class F, class Args >
    struct sig_impl< F, Args, n > :
        boost::result_of<
            F(
                BOOST_PP_ENUM(n, PSTADE_element, ~)
            )
        >
    { };


#undef n
#endif
