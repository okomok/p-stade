#ifndef BOOST_PP_IS_ITERATING
#ifndef PSTADE_EGG_BABY_CALL_HPP
#define PSTADE_EGG_BABY_CALL_HPP


// PStade.Egg
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/preprocessor/iteration/iterate.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <pstade/preprocessor.hpp>
#include "./baby_result.hpp"
#include "./detail/config.hpp"


namespace pstade { namespace egg {


// 0ary
//
template< class BabyFunction > inline
typename baby_result0<BabyFunction>::type
baby_call(BabyFunction& baby)
{
    typedef typename baby_result0<BabyFunction
    >::type result_t;

    return baby.template call<result_t>();
}


// 1ary
//
template< class BabyFunction, class A0 > inline
typename egg::baby_result1<BabyFunction,
    A0&
>::type
baby_call(BabyFunction& baby, A0& a0)
{
    typedef typename egg::baby_result1<BabyFunction,
        A0&
    >::type result_t;

    return baby.template call<result_t>(a0);
}


// 2ary -
//
#define BOOST_PP_ITERATION_PARAMS_1 (3, (2, PSTADE_EGG_MAX_ARITY, <pstade/egg/baby_call.hpp>))
#include BOOST_PP_ITERATE()


} } // namespace pstade::egg


#endif
#else
#define n BOOST_PP_ITERATION()


template< class BabyFunction, BOOST_PP_ENUM_PARAMS(n, class A) > inline
typename BOOST_PP_CAT(baby_result, n)<BabyFunction,
    PSTADE_PP_ENUM_REF_PARAMS(n, A)
>::type
baby_call( BabyFunction& baby, PSTADE_PP_ENUM_REF_PARAMS_WITH_OBJECTS(n, A, a) )
{
    typedef typename BOOST_PP_CAT(baby_result, n)<BabyFunction,
        PSTADE_PP_ENUM_REF_PARAMS(n, A)
    >::type result_t;

    return baby.template call<result_t>( BOOST_PP_ENUM_PARAMS(n, a) );
}


#undef n
#endif
