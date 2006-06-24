#ifndef PSTADE_EGG_BABY_CALL_HPP
#define PSTADE_EGG_BABY_CALL_HPP


// PStade.Egg
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/preprocessor/arithmetic/inc.hpp>
#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/repetition/enum.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/preprocessor/repetition/repeat_from_to.hpp>
#include "./baby_result_type.hpp"
#include "./detail/config.hpp"


namespace pstade { namespace egg {


// 0ary
//
template< class BabyFunction > inline
typename baby_result0<BabyFunction>::type
baby_call()
{
    typedef typename baby_result0<BabyFunction
    >::type result_t;

    return BabyFunction().template call<result_t>();
}


// 1ary
//
template< class BabyFunction, class A0 >
typename egg::baby_result1<BabyFunction,
    A0
>::type
baby_call(A0& a0)
{
    typedef typename egg::baby_result1<BabyFunction,
        A0
    >::type result_t;

    return BabyFunction().template call<result_t>(a0);
}


// 2ary
//
template< class BabyFunction, class A0, class A1 >
typename egg::baby_result2<BabyFunction,
    A0, A1
>::type
baby_call(A0& a0, A1& a1)
{
    typedef typename egg::baby_result2<BabyFunction,
        A0, A1
    >::type result_t;

    return BabyFunction().template call<result_t>(a0, a1);
}


// 3ary -
//
#define PSTADE_EGG_baby_call(Z, N, _) \
    template< class BabyFunction, BOOST_PP_ENUM_PARAMS(N, class A) > inline \
    typename BOOST_PP_CAT(baby_result, N)<BabyFunction, \
        BOOST_PP_ENUM_PARAMS(N, A) \
    >::type \
    baby_call( BOOST_PP_ENUM(N, PSTADE_EGG_arg, ~) ) \
    { \
        typedef typename BOOST_PP_CAT(baby_result, N)<BabyFunction, \
            BOOST_PP_ENUM_PARAMS(N, A) \
        >::type result_t; \
        \
        return BabyFunction().template call<result_t>( BOOST_PP_ENUM_PARAMS(N, a) ); \
    } \
/**/

#define PSTADE_EGG_arg(Z, N, _) \
    BOOST_PP_CAT(A, N) & BOOST_PP_CAT(a, N) \
/**/

BOOST_PP_REPEAT_FROM_TO(3, BOOST_PP_INC(PSTADE_EGG_MAX_ARITY), PSTADE_EGG_baby_call, ~)

#undef PSTADE_EGG_arg
#undef PSTADE_EGG_baby_call


} } // namespace pstade::egg


#endif
