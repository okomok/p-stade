#ifndef BOOST_PP_IS_ITERATING
#ifndef PSTADE_PROVIDE_RESULT_OF_SIG_HPP
#define PSTADE_PROVIDE_RESULT_OF_SIG_HPP


// PStade.Wine
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/config.hpp> // BOOST_NESTED_TEMPLATE
#include <boost/preprocessor/iteration/iterate.hpp>
#include <boost/preprocessor/repetition/enum_binary_params.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/tuple/tuple.hpp>
#include <pstade/adl_barrier.hpp>
#include <pstade/callable.hpp> // callable_argument
#include <pstade/preprocessor.hpp>


#if !defined(PSTADE_PROVIDE_RESULT_OF_SIG_MAX_ARITY)
    #define PSTADE_PROVIDE_RESULT_OF_SIG_MAX_ARITY 9 // follows 'tuple'.
#endif


namespace pstade {


PSTADE_ADL_BARRIER(provide_result_of_sig) {


    struct provide_result_of_sig
    {
        template<class FunCall>
        struct result
        { }; // complete for SFINAE

        #define  BOOST_PP_ITERATION_PARAMS_1 (3, (1, PSTADE_PROVIDE_RESULT_OF_SIG_MAX_ARITY, <pstade/provide_result_of_sig.hpp>))
        #include BOOST_PP_ITERATE()
    };


} // ADL barrier


#define PSTADE_NULLARY_RESULT_OF_SIG_TYPE(X) \
    namespace boost { \
        \
        template< > \
        struct result_of< X(void) > : \
            X::sig< \
                tuples::tuple< X > \
            > \
        { }; \
        \
        template< > \
        struct result_of< X const(void) > : \
               result_of< X(void) > \
        { }; \
        \
    } \
/**/


#define PSTADE_NULLARY_RESULT_OF_SIG_TEMPLATE(X, SeqOrNum) \
    PSTADE_NULLARY_RESULT_OF_SIG_TEMPLATE_aux(X, PSTADE_PP_TO_TEMPLATE_PARAM_SEQ(SeqOrNum)) \
/**/

    #define PSTADE_NULLARY_RESULT_OF_SIG_TEMPLATE_aux(X, Seq) \
        namespace boost { \
            \
            template<PSTADE_PP_TO_TEMPLATE_PARAMS(Seq, T)> \
            struct result_of< X<PSTADE_PP_TO_TEMPLATE_ARGS(Seq, T)>(void) > : \
                X<PSTADE_PP_TO_TEMPLATE_ARGS(Seq, T)>::BOOST_NESTED_TEMPLATE sig< \
                    tuples::tuple< X<PSTADE_PP_TO_TEMPLATE_ARGS(Seq, T)> > \
                > \
            { }; \
            \
            template<PSTADE_PP_TO_TEMPLATE_PARAMS(Seq, T)> \
            struct result_of< X<PSTADE_PP_TO_TEMPLATE_ARGS(Seq, T)> const(void) > : \
                   result_of< X<PSTADE_PP_TO_TEMPLATE_ARGS(Seq, T)>(void) > \
            { }; \
            \
        } \
    /**/


} // namespace pstade


#endif
#else
#define n BOOST_PP_ITERATION()


template<class Fun, BOOST_PP_ENUM_PARAMS(n, class A)>
struct result<Fun(BOOST_PP_ENUM_PARAMS(n, A))> :
    Fun::BOOST_NESTED_TEMPLATE sig<
        boost::tuples::tuple<
            Fun,
            PSTADE_PP_ENUM_PARAMS_WITH(n, typename callable_argument<A, >::type)
        >
    >
{ };


#undef n
#endif
