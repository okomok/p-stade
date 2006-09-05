#ifndef BOOST_PP_IS_ITERATING
#ifndef PSTADE_EGG_DETAIL_RESULT_OFS_HPP
#define PSTADE_EGG_DETAIL_RESULT_OFS_HPP


// PStade.Egg
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// Why not: nested 'result'
//
// The nested 'result' makes name-collision with BabyFunction's 'result'.
// Moreover, nested type specializations seem not to work under VC++.


#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/iteration/iterate.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/utility/result_of.hpp>
#include "../baby_result.hpp"
#include "../function_fwd.hpp"
#include "./config.hpp"


namespace boost {


    // 0ary
    //
    template< class BabyFunction >
    struct result_of<pstade::egg::function<BabyFunction>(void)> : // CWPro8 requires an argument 'void'
        pstade::egg::baby_result0<BabyFunction>
    { };


    // 1ary
    //
    template< class BabyFunction, class A0 >
    struct result_of<pstade::egg::function<BabyFunction>(A0)> :
        pstade::egg::baby_result1<BabyFunction, A0>
    { };


    // 2ary
    //
    template< class BabyFunction, class A0, class A1 >
    struct result_of<pstade::egg::function<BabyFunction>(A0, A1)> :
        pstade::egg::baby_result2<BabyFunction, A0, A1>
    { };


    // 3ary -
    //
    #define BOOST_PP_ITERATION_PARAMS_1 (3, (3, PSTADE_EGG_MAX_ARITY, <pstade/egg/detail/result_ofs.hpp>))
    #include BOOST_PP_ITERATE()


} // namespace boost


#endif
#else
#define n BOOST_PP_ITERATION()


template< class BabyFunction, BOOST_PP_ENUM_PARAMS(n, class A) >
struct result_of<pstade::egg::function<BabyFunction>( BOOST_PP_ENUM_PARAMS(n, A) )> :
    pstade::egg::BOOST_PP_CAT(baby_result, n)< BabyFunction, BOOST_PP_ENUM_PARAMS(n, A) >
{ };


#undef n
#endif
