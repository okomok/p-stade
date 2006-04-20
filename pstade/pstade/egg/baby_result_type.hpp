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
#include <boost/type_traits/remove_reference.hpp>
#include <boost/utility/result_of.hpp>
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


// numbered forms
//
template< class BabyFunction >
struct baby_result0 :
    boost::mpl::eval_if<detail::has_result_type<BabyFunction>,
        baby_result_type_detail::nullary<BabyFunction>,
        boost::mpl::identity<error_no_arguments_supplied>
    >
{ };


template< class BabyFunction, class A0 >
struct baby_result1 :
    boost::mpl::apply1<BabyFunction, 
        typename boost::remove_reference<A0>::type
    >
{ };


template< class BabyFunction, class A0, class A1 >
struct baby_result2 :
    boost::mpl::apply2<BabyFunction,
        typename boost::remove_reference<A0>::type,
        typename boost::remove_reference<A1>::type
    >
{ };


template< class BabyFunction, class A0, class A1, class A2 >
struct baby_result3 :
    boost::mpl::apply3<BabyFunction,
        typename boost::remove_reference<A0>::type,
        typename boost::remove_reference<A1>::type,
        typename boost::remove_reference<A2>::type
    >
{ };


// variadic form
//
// TODO


} } // namespace pstade::egg


#endif
