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


#include <boost/preprocessor/iteration/iterate.hpp>
#include <boost/preprocessor/repetition/enum.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/tuple/tuple.hpp>
#include <pstade/egg/function.hpp>
#include <pstade/egg/pipable.hpp>


namespace pstade {


    namespace tie_detail {


        struct baby
        {
            // 5ary (primary)
            template< class Myself, class A0, class A1 = void, class A2 = void, class A3 = void, class A4 = void >
            struct apply
            {
                typedef boost::tuples::tuple<A0&, A1&, A2&, A3&, A4&> type;
            };

            template< class Result, class A0, class A1, class A2, class A3, class A4 >
            Result call(A0& a0, A1& a1, A2& a2, A3& a3, A4& a4)
            {
                return Result(a0, a1, a2, a3, a4);
            }

            // 1ary
            template< class Myself, class A0 >
            struct apply< Myself, A0 >
            {
                typedef boost::tuples::tuple<A0&> type;
            };

            template< class Result, class A0>
            Result call(A0& a0)
            {
                return Result(a0);
            }

            // 2ary-4ary
        #define PSTADE_max_arity 4
        #define PSTADE_add_ref(Z, N, _) BOOST_PP_CAT(A, N) &
        #define PSTADE_ref_param(Z, N, _) BOOST_PP_CAT(A, N) & BOOST_PP_CAT(a, N)
            #define BOOST_PP_ITERATION_PARAMS_1 (3, (2, PSTADE_max_arity, <pstade/tie.hpp>))
            #include BOOST_PP_ITERATE()
        #undef PSTADE_ref_param
        #undef PSTADE_add_ref
        #undef PSTADE_max_arity

        }; // baby


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
