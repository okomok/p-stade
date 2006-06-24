#ifndef PSTADE_EGG_BABY_RESULT_TYPE_HPP
#define PSTADE_EGG_BABY_RESULT_TYPE_HPP


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
#include <boost/preprocessor/arithmetic/inc.hpp>
#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/repetition/enum.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/preprocessor/repetition/repeat_from_to.hpp>
#include <boost/type_traits/remove_reference.hpp>
#include <boost/utility/result_of.hpp>
#include "./detail/config.hpp"
#include "./detail/has_result_type.hpp"


namespace pstade { namespace egg {


namespace baby_result_type_detail {


    template< class BabyFunction >
    struct nullary
    {
        typedef typename BabyFunction::result_type type;
    };


} // namespace baby_result_type_detail


struct error_no_arguments_supplied
{
    template< class T >
    error_no_arguments_supplied(const T&)
    { }
};


template< class BabyFunction >
struct baby_result0 :
    boost::mpl::eval_if<detail::has_result_type<BabyFunction>,
        baby_result_type_detail::nullary<BabyFunction>,
        boost::mpl::identity<error_no_arguments_supplied>
    >
{ };


/*
template< class BabyFunction, class A0, class A1 >
struct baby_result2 :
    BabyFunction::template result<
        typename boost::remove_reference<A0>::type,
        typename boost::remove_reference<A1>::type
    >
{ };
*/


#define PSTADE_EGG_baby_result(Z, N, _) \
    template< class BabyFunction, BOOST_PP_ENUM_PARAMS(N, class A) > \
    struct BOOST_PP_CAT(baby_result, N) : \
        BabyFunction::template result< \
            BOOST_PP_ENUM(N, PSTADE_EGG_remove_ref, ~) \
        > \
    { }; \
/**/


#define PSTADE_EGG_remove_ref(Z, N, _) \
    typename boost::remove_reference< BOOST_PP_CAT(A, N) >::type \
/**/


BOOST_PP_REPEAT_FROM_TO(1, BOOST_PP_INC(PSTADE_EGG_MAX_ARITY), PSTADE_EGG_baby_result, ~)


#undef PSTADE_EGG_remove_ref
#undef PSTADE_EGG_baby_result


} } // namespace pstade::egg


#endif
