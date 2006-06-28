#ifndef BOOST_PP_IS_ITERATING
#ifndef PSTADE_EGG_DETAIL_RESULTS_HPP
#define PSTADE_EGG_DETAIL_RESULTS_HPP


// PStade.Egg
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/preprocessor/iteration/iterate.hpp>
#include "./config.hpp"
#include "../baby_result_type.hpp"


namespace pstade { namespace egg { namespace detail {


template< class BabyFunction >
struct results
{

#if !defined(PSTADE_EGG_DETAIL_NO_NESTED_RESULT_SPECIALIZATION)


    template< class F_Args >
    struct result;


    // 1ary
    //
    template< class F_, class A0 >
    struct result<F_(A0)> :
        baby_result1<BabyFunction, A0>
    { };


    // 2ary
    //
    template< class F_, class A0, class A1 >
    struct result<F_(A0, A1)> :
        baby_result2<BabyFunction, A0, A1>
    { };


    // 3ary -
    //
    #define BOOST_PP_ITERATION_PARAMS_1 (3, (3, PSTADE_EGG_MAX_ARITY, <pstade/egg/detail/results.hpp>))
    #include BOOST_PP_ITERATE()


#endif

}; // struct results


} } } // namespace pstade::egg::detail


#endif
#else
#define n BOOST_PP_ITERATION()


template< class F_, BOOST_PP_ENUM_PARAMS(n, class A) >
struct result< F_( BOOST_PP_ENUM_PARAMS(n, A) ) > :
    BOOST_PP_CAT(baby_result, n)< BabyFunction, BOOST_PP_ENUM_PARAMS(n, A) >
{ };


#undef n
#endif
