#ifndef BOOST_PP_IS_ITERATING
#ifndef PSTADE_EGG_DETAIL_FREE_CALL_HPP
#define PSTADE_EGG_DETAIL_FREE_CALL_HPP


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/preprocessor/iteration/iterate.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/preprocessor/repetition/enum_trailing_binary_params.hpp>
#include <boost/preprocessor/repetition/enum_trailing_params.hpp>
#include "../config.hpp" // PSTADE_EGG_MAX_LINEAR_ARITY
#include "./get_pointer_preamble.hpp"


namespace pstade { namespace egg { namespace detail {


    #define  BOOST_PP_ITERATION_PARAMS_1 (3, (0, PSTADE_EGG_MAX_LINEAR_ARITY, <pstade/egg/detail/free_call.hpp>))
    #include BOOST_PP_ITERATE()


} } } // namespace pstade::egg::detail


#endif
#else
#define n BOOST_PP_ITERATION()


    template<class Re, class To, class Ptr, class From BOOST_PP_ENUM_TRAILING_PARAMS(n, class A)> inline
    Re free_call_aux(Ptr ptr, From &from, To const *   BOOST_PP_ENUM_TRAILING_BINARY_PARAMS(n, A, &a))
    {
        return (from.*ptr)(BOOST_PP_ENUM_PARAMS(n, a));
    }

    template<class Re, class To, class Ptr, class From BOOST_PP_ENUM_TRAILING_PARAMS(n, class A)> inline
    Re free_call_aux(Ptr ptr, From &from, void const * BOOST_PP_ENUM_TRAILING_BINARY_PARAMS(n, A, &a))
    {
        PSTADE_EGG_GET_POINTER_PREAMBLE()
        return (get_pointer(from)->*ptr)(BOOST_PP_ENUM_PARAMS(n, a));
    }


    template<class Re, class To, class Ptr, class From BOOST_PP_ENUM_TRAILING_PARAMS(n, class A)> inline
    Re free_call(Ptr ptr, From &from BOOST_PP_ENUM_TRAILING_BINARY_PARAMS(n, A, &a))
    {
        return detail::free_call_aux<Re, To>(ptr, from, &from BOOST_PP_ENUM_TRAILING_PARAMS(n, a));
    }


#undef  n
#endif
