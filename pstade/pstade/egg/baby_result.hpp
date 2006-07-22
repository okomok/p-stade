#ifndef BOOST_PP_IS_ITERATING
#ifndef PSTADE_EGG_BABY_RESULT_HPP
#define PSTADE_EGG_BABY_RESULT_HPP


// PStade.Egg
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// See: <boost/phoenix/core/actor.hpp>
//
/*=============================================================================
    Copyright (c) 2001-2004 Joel de Guzman

    Use, modification and distribution is subject to the Boost Software
    License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
    http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/


#include <boost/mpl/apply.hpp>
#include <boost/mpl/eval_if.hpp>
#include <boost/mpl/identity.hpp>
#include <boost/mpl/void.hpp>
#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/iteration/iterate.hpp>
#include <boost/preprocessor/repetition/enum.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/type_traits/remove_reference.hpp>
#include <pstade/has_xxx.hpp>
#include "./detail/config.hpp"


namespace pstade { namespace egg {


namespace baby_result_detail {


    PSTADE_HAS_TYPE(nullary_result_type)


    template< class BabyFunction >
    struct nullary
    {
        typedef typename BabyFunction::nullary_result_type type;
    };


    typedef boost::mpl::void_
    dummy_type;


} // namespace baby_result_detail


struct error_no_arguments_supplied
{
    template< class T >
    error_no_arguments_supplied(const T&)
    { }
};


// 0ary
//
template< class BabyFunction >
struct baby_result0 :
    boost::mpl::eval_if< baby_result_detail::has_nullary_result_type<BabyFunction>,
        baby_result_detail::nullary<BabyFunction>,
        boost::mpl::identity<error_no_arguments_supplied>
    >
{ };


// 1ary
//
template< class BabyFunction, class A0 >
struct baby_result1 :
    BabyFunction::template result<
        baby_result_detail::dummy_type,
        typename boost::remove_reference<A0>::type
    >
{ };


// 2ary
//
template< class BabyFunction, class A0, class A1 >
struct baby_result2 :
    BabyFunction::template result<
        baby_result_detail::dummy_type,
        typename boost::remove_reference<A0>::type,
        typename boost::remove_reference<A1>::type
    >
{ };


// 3ary -
//
#define PSTADE_EGG_remove_ref(Z, N, _) \
    typename boost::remove_reference< BOOST_PP_CAT(A, N) >::type \
/**/

#define BOOST_PP_ITERATION_PARAMS_1 (3, (3, PSTADE_EGG_MAX_ARITY, <pstade/egg/baby_result.hpp>))
#include BOOST_PP_ITERATE()

#undef PSTADE_EGG_remove_ref


} } // namespace pstade::egg


#endif
#else
#define n BOOST_PP_ITERATION()


template< class BabyFunction, BOOST_PP_ENUM_PARAMS(n, class A) >
struct BOOST_PP_CAT(baby_result, n) :
    BabyFunction::template result<
        baby_result_detail::dummy_type,
        BOOST_PP_ENUM(n, PSTADE_EGG_remove_ref, ~)
    >
{ };


#undef n
#endif
