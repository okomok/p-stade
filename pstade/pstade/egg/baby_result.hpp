#ifndef BOOST_PP_IS_ITERATING
#ifndef PSTADE_EGG_BABY_RESULT_HPP
#define PSTADE_EGG_BABY_RESULT_HPP


// PStade.Egg
//
// Copyright Shunsuke Sogame 2005-2006.
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


// Note:
//
// Assume there is no 'nullary_result_type' mechanism.
// As [1] mentions, 'boost::result_of<F()>::type' must always be valid,
// which implies that 'Baby::apply<Myself>::type' must be;
// even if 'F' object is never called without arguments.
// It would be very cumbersome.
//
// [1] http://anubis.dkuug.dk/jtc1/sc22/wg21/docs/papers/2003/n1454.html


#include <boost/mpl/eval_if.hpp>
#include <boost/mpl/identity.hpp>
#include <boost/mpl/not.hpp>
#include <boost/mpl/void.hpp>
#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/iteration/iterate.hpp>
#include <boost/preprocessor/repetition/enum.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/type_traits/add_const.hpp>
#include <boost/type_traits/is_reference.hpp>
#include <boost/type_traits/remove_reference.hpp>
#include <pstade/has_xxx.hpp>
#include "./detail/config.hpp"


namespace pstade { namespace egg {


namespace baby_result_detail {


    PSTADE_HAS_TYPE(nullary_result_type)


    template< class BabyFunction >
    struct nullary_result
    {
        typedef typename BabyFunction::nullary_result_type type;
    };


    template< class A >
    struct meta_arg :
        boost::mpl::eval_if< boost::mpl::not_< boost::is_reference<A> >,
            boost::add_const<A>,
            boost::remove_reference<A>
        >
    { };


} // namespace baby_result_detail


struct error_no_arguments_supplied
{
    template< class T >
    error_no_arguments_supplied(T const&)
    { }
};


// 0ary
//
template< class BabyFunction >
struct baby_result0 :
    boost::mpl::eval_if< baby_result_detail::has_nullary_result_type<BabyFunction>,
        baby_result_detail::nullary_result<BabyFunction>,
        boost::mpl::identity<error_no_arguments_supplied>
    >
{ };


// 1ary
//
template< class BabyFunction, class A0 >
struct baby_result1 :
    BabyFunction::template apply<BabyFunction,
        typename baby_result_detail::meta_arg<A0>::type
    >
{ };


// 2ary -
//
#define PSTADE_EGG_meta_arg(Z, N, _) \
    typename baby_result_detail::meta_arg< BOOST_PP_CAT(A, N) >::type \
/**/

#define BOOST_PP_ITERATION_PARAMS_1 (3, (2, PSTADE_EGG_MAX_ARITY, <pstade/egg/baby_result.hpp>))
#include BOOST_PP_ITERATE()

#undef PSTADE_EGG_meta_arg


} } // namespace pstade::egg


#endif
#else
#define n BOOST_PP_ITERATION()


template< class BabyFunction, BOOST_PP_ENUM_PARAMS(n, class A) >
struct BOOST_PP_CAT(baby_result, n) :
    BabyFunction::template apply<BabyFunction,
        BOOST_PP_ENUM(n, PSTADE_EGG_meta_arg, ~)
    >
{ };


#undef n
#endif
