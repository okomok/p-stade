#ifndef BOOST_PP_IS_ITERATING
#ifndef BOOST_EGG_DETAIL_FREE_CALL_HPP
#define BOOST_EGG_DETAIL_FREE_CALL_HPP


// Boost.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/preprocessor/iteration/iterate.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/preprocessor/repetition/enum_trailing_binary_params.hpp>
#include <boost/preprocessor/repetition/enum_trailing_params.hpp>
#include <boost/egg/config.hpp> // BOOST_EGG_MAX_LINEAR_ARITY
#include <boost/egg/detail/get_pointer_preamble.hpp>


namespace boost { namespace egg { namespace details {


    #define  BOOST_PP_ITERATION_PARAMS_1 (3, (0, BOOST_EGG_MAX_LINEAR_ARITY, <boost/egg/detail/free_call.hpp>))
    #include BOOST_PP_ITERATE()


} } } // namespace boost::egg::details


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
        BOOST_EGG_GET_POINTER_PREAMBLE()
        return (get_pointer(from)->*ptr)(BOOST_PP_ENUM_PARAMS(n, a));
    }


    template<class Re, class To, class Ptr, class From BOOST_PP_ENUM_TRAILING_PARAMS(n, class A)> inline
    Re free_call(Ptr ptr, From &from BOOST_PP_ENUM_TRAILING_BINARY_PARAMS(n, A, &a))
    {
        return details::free_call_aux<Re, To>(ptr, from, &from BOOST_PP_ENUM_TRAILING_PARAMS(n, a));
    }


#undef  n
#endif
