#ifndef BOOST_PP_IS_ITERATING
#ifndef PSTADE_TIE_HPP
#define PSTADE_TIE_HPP


// PStade.Wine
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// What:
//
// Supports rvalue and const-reference.


#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/arithmetic/dec.hpp>
#include <boost/preprocessor/iteration/iterate.hpp>
#include <boost/preprocessor/repetition/enum.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/preprocessor/repetition/enum_params_with_a_default.hpp>
#include <boost/tuple/tuple.hpp>
#include <pstade/egg/function.hpp>
#include <pstade/egg/pipable.hpp>


namespace pstade {


    namespace tie_detail {


        struct baby
        {

        #define PSTADE_add_ref(Z, N, _)   BOOST_PP_CAT(A, N) &
        #define PSTADE_ref_param(Z, N, _) BOOST_PP_CAT(A, N) & BOOST_PP_CAT(a, N)

            // PSTADE_EGG_MAX_ARITY (primary)
            template< class Myself, BOOST_PP_ENUM_PARAMS_WITH_A_DEFAULT(PSTADE_EGG_MAX_ARITY, class A, void) >
            struct apply
            {
                typedef boost::tuples::tuple< BOOST_PP_ENUM(PSTADE_EGG_MAX_ARITY, PSTADE_add_ref, ~) > type;
            };

            template< class Result, class A0, class A1, class A2, class A3, class A4 >
            Result call( BOOST_PP_ENUM(PSTADE_EGG_MAX_ARITY, PSTADE_ref_param, ~) )
            {
                return Result( BOOST_PP_ENUM_PARAMS(PSTADE_EGG_MAX_ARITY, a) );
            }

            // 1ary
            template< class Myself, class A0 >
            struct apply< Myself, A0 >
            {
                typedef boost::tuples::tuple< A0& > type;
            };

            template< class Result, class A0>
            Result call( A0& a0 )
            {
                return Result( a0 );
            }

            // 2ary-
        #define PSTADE_max_arity BOOST_PP_DEC(PSTADE_EGG_MAX_ARITY)
            #define  BOOST_PP_ITERATION_PARAMS_1 (3, (2, PSTADE_max_arity, <pstade/tie.hpp>))
            #include BOOST_PP_ITERATE()
        #undef  PSTADE_max_arity

        #undef PSTADE_ref_param
        #undef PSTADE_add_ref

        }; // struct baby


    } // namespace tie_detail


    PSTADE_EGG_FUNCTION(tie, tie_detail::baby)
    PSTADE_EGG_PIPABLE(tied, tie_detail::baby)


} // namespace pstade


#endif
#else
#define n BOOST_PP_ITERATION()


template< class Myself, BOOST_PP_ENUM_PARAMS(n, class A) >
struct apply< Myself, BOOST_PP_ENUM_PARAMS(n, A) >
{
    typedef boost::tuples::tuple< BOOST_PP_ENUM(n, PSTADE_add_ref, ~) > type;
};

template< class Result, BOOST_PP_ENUM_PARAMS(n, class A) >
Result call( BOOST_PP_ENUM(n, PSTADE_ref_param, ~) )
{
    return Result( BOOST_PP_ENUM_PARAMS(n, a) );
}


#undef n
#endif
