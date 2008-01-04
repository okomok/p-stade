#ifndef BOOST_PP_IS_ITERATING
#ifndef PSTADE_EGG_DETAIL_LITTLE_UNCURRY_RESULT_HPP
#define PSTADE_EGG_DETAIL_LITTLE_UNCURRY_RESULT_HPP
#include "./prefix.hpp"


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/iteration/iterate.hpp>
#include <boost/preprocessor/repetition/enum_binary_params.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/preprocessor/repetition/repeat.hpp>
#include <pstade/pod_constant.hpp>
#include <pstade/result_of.hpp>
#include "../apply_decl.hpp"
#include "../config.hpp" // PSTADE_EGG_MAX_ARITY


namespace pstade { namespace egg { namespace detail {


    template<class Base>
    struct little_uncurry_result
    {
        Base m_base;

        typedef Base base_type;

        Base base() const
        {
            return m_base;
        }

    // 1ary-
        template<class Myself, PSTADE_EGG_APPLY_DECL_PARAMS(PSTADE_EGG_MAX_ARITY, A)>
        struct PSTADE_EGG_APPLY_DECL;

    #define PSTADE_open_result_of(Z, N, _)  typename result_of<
    #define PSTADE_close_result_of(Z, N, _) >::type(BOOST_PP_CAT(A, N)&)
    #define PSTADE_paren(Z, N, _) ( BOOST_PP_CAT(a, N) )
        #define  BOOST_PP_ITERATION_PARAMS_1 (3, (1, PSTADE_EGG_MAX_ARITY, <pstade/egg/detail/little_uncurry_result.hpp>))
        #include BOOST_PP_ITERATE()
    #undef  PSTADE_paren
    #undef  PSTADE_close_result_of
    #undef  PSTADE_open_result_of
    };


} } } // namespace pstade::egg::detail


#endif
#else
#define n BOOST_PP_ITERATION()


    template<class Myself, BOOST_PP_ENUM_PARAMS(n, class A)>
    struct apply<Myself, BOOST_PP_ENUM_PARAMS(n, A)> :
        result_of<
            BOOST_PP_REPEAT_FROM_TO(1, n, PSTADE_open_result_of, ~)
                Base const(A0&)
            BOOST_PP_REPEAT_FROM_TO(1, n, PSTADE_close_result_of, ~)
        >      
    { };

    template<class Result, BOOST_PP_ENUM_PARAMS(n, class A)>
    Result call(BOOST_PP_ENUM_BINARY_PARAMS(n, A, & a)) const
    {
        return m_base BOOST_PP_REPEAT(n, PSTADE_paren, ~) ;
    }
    

#undef n
#endif
