#ifndef PSTADE_AFFECT_HPP
#define PSTADE_AFFECT_HPP
#include "./detail/prefix.hpp"


// PStade.Wine
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// Note:
//
// The name "affect" comes from C++ Standard 9.3.1/4.
// If a member is reference, it is not affected.
// You can find the same strategy in 'boost::tuples::access_traits'.


#include <boost/mpl/eval_if.hpp>
#include <boost/mpl/identity.hpp>
#include <boost/type_traits/add_const.hpp>
#include <boost/type_traits/add_reference.hpp>
#include <boost/type_traits/add_volatile.hpp>
#include <boost/type_traits/is_const.hpp>
#include <boost/type_traits/is_reference.hpp>
#include <boost/type_traits/is_volatile.hpp>
#include <boost/type_traits/remove_reference.hpp>


namespace pstade {


    template<class From, class To>
    struct affect_const :
        boost::mpl::eval_if< boost::is_const<From>,
            boost::add_const<To>,
            boost::mpl::identity<To>
        >
    { };


    template<class From, class To>
    struct affect_volatile :
        boost::mpl::eval_if< boost::is_volatile<From>,
            boost::add_volatile<To>,
            boost::mpl::identity<To>
        >
    { };


    template<class From, class To>
    struct affect_cv :
        affect_const<From,
            typename affect_volatile<From, To>::type
        >
    { };


    template<class From, class To>
    struct affect_reference :
        boost::mpl::eval_if< boost::is_reference<From>,
            boost::add_reference<To>,
            boost::mpl::identity<To>
        >
    { };


    template<class From, class To>
    struct affect
    {
        typedef
            typename boost::remove_reference<From>::type
        non_ref_from;

        typedef
            typename affect_reference<From,
                typename affect_cv<non_ref_from, To>::type
            >::type
        type;
    };


} // namespace pstade


#endif
