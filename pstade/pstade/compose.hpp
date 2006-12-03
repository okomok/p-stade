#ifndef BOOST_PP_IS_ITERATING
#ifndef PSTADE_COMPOSE_HPP
#define PSTADE_COMPOSE_HPP


// PStade.Wine
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/arithmetic/dec.hpp>
#include <boost/preprocessor/iteration/iterate.hpp>
#include <boost/preprocessor/repetition/enum.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/preprocessor/repetition/enum_params_with_a_default.hpp>
#include <boost/utility/result_of.hpp>
#include <pstade/egg/function.hpp>
#include <pstade/egg/pipable.hpp>
#include <pstade/pass_by.hpp>


namespace pstade {


    namespace compose_detail {


        template< class F, class GSig >
        struct result_of_aux :
            boost::result_of<
                F(
                    typename boost::result_of<GSig>::type
                )
            >
        { };


        template< class F, class G >
        struct baby_fun
        {

        #define PSTADE_add_ref(Z, N, _)   BOOST_PP_CAT(A, N) &
        #define PSTADE_ref_param(Z, N, _) BOOST_PP_CAT(A, N) & BOOST_PP_CAT(a, N)

            // PSTADE_EGG_MAX_ARITY (primary)
            template< class Myself, BOOST_PP_ENUM_PARAMS_WITH_A_DEFAULT(PSTADE_EGG_MAX_ARITY, class A, void) >
            struct apply :
                result_of_aux< F, G(
                    BOOST_PP_ENUM(PSTADE_EGG_MAX_ARITY, PSTADE_add_ref, ~)
                ) >
            { };

            template< class Result, BOOST_PP_ENUM_PARAMS(PSTADE_EGG_MAX_ARITY, class A) >
            Result call( BOOST_PP_ENUM(PSTADE_EGG_MAX_ARITY, PSTADE_ref_param, ~) )
            {
                return m_f( m_g(
                    BOOST_PP_ENUM_PARAMS(PSTADE_EGG_MAX_ARITY, a)
                ) );
            }

            // 0ary
            typedef typename
                result_of_aux< F, G(
                ) >::type
            nullary_result_type;

            template< class Result >
            Result call( )
            {
                return m_f( m_g(
                ) );
            }

            // 1ary
            template< class Myself, class A0 >
            struct apply< Myself, A0 > :
                result_of_aux< F, G(
                    A0&
                ) >
            { };

            template< class Result, class A0 >
            Result call( A0& a0 )
            {
                return m_f( m_g(
                    a0
                ) );
            }

            // 2ary-
        #define PSTADE_max_arity BOOST_PP_DEC(PSTADE_EGG_MAX_ARITY)
            #define  BOOST_PP_ITERATION_PARAMS_1 (3, (2, PSTADE_max_arity, <pstade/compose.hpp>))
            #include BOOST_PP_ITERATE()
        #undef  PSTADE_max_arity

        #undef  PSTADE_ref_param
        #undef  PSTADE_add_ref

            explicit baby_fun() // DefaultConstructible iff 'F' and 'G' is.
            { }

            explicit baby_fun(F const& f, G const& g) :
                m_f(f), m_g(g)
            { }

        private:
            F m_f;
            G m_g;

        }; // struct baby_fun


        struct baby
        {
            template< class Myself, class F, class G >
            struct apply
            {
                typedef egg::function<
                    baby_fun<
                        typename pass_by_value<F>::type,
                        typename pass_by_value<G>::type
                    >
                > type;
            };

            template< class Result, class F, class G >
            Result call(F& f, G& g)
            {
                return Result(f, g);
            }
        };


    } // namespace compose_detail


    PSTADE_EGG_FUNCTION(compose, compose_detail::baby)
    PSTADE_EGG_PIPABLE(composed, compose_detail::baby)


} // namespace pstade


#endif
#else
#define n BOOST_PP_ITERATION()


template< class Myself, BOOST_PP_ENUM_PARAMS(n, class A) >
struct apply< Myself, BOOST_PP_ENUM_PARAMS(n, A) > :
    result_of_aux< F, G(
        BOOST_PP_ENUM(n, PSTADE_add_ref, ~)
    ) >
{ };

template< class Result, BOOST_PP_ENUM_PARAMS(n, class A) >
Result call( BOOST_PP_ENUM(n, PSTADE_ref_param, ~) )
{
    return m_f( m_g(
        BOOST_PP_ENUM_PARAMS(n, a)
    ) );
}


#undef n
#endif
