#ifndef PSTADE_EGG_DETAIL_RESULTS_HPP
#define PSTADE_EGG_DETAIL_RESULTS_HPP


// PStade.Egg
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/preprocessor/arithmetic/inc.hpp>
#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/preprocessor/repetition/repeat_from_to.hpp>
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
    #define PSTADE_EGG_result(Z, N, _) \
        template< class F_, BOOST_PP_ENUM_PARAMS(N, class A) > \
        struct result< F_( BOOST_PP_ENUM_PARAMS(N, A) ) > : \
            BOOST_PP_CAT(baby_result, N)< BabyFunction, BOOST_PP_ENUM_PARAMS(N, A) > \
        { }; \
    /**/

    BOOST_PP_REPEAT_FROM_TO(3, BOOST_PP_INC(PSTADE_EGG_MAX_ARITY), PSTADE_EGG_result, ~)

    #undef PSTADE_EGG_result


#endif
};


} } } // namespace pstade::egg::detail


#endif
