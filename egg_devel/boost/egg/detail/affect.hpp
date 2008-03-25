#ifndef BOOST_EGG_DETAIL_AFFECT_HPP
#define BOOST_EGG_DETAIL_AFFECT_HPP


// Boost.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// Note:
//
// The name "affect" comes from C++ Standard 9.3.1/4.
// If a member is reference, it is not affected.
// You can find the same strategy in `tuples::access_traits`.


#include <boost/mpl/eval_if.hpp>
#include <boost/mpl/identity.hpp>
#include <boost/type_traits/add_const.hpp>
#include <boost/type_traits/add_reference.hpp>
#include <boost/type_traits/add_volatile.hpp>
#include <boost/type_traits/is_const.hpp>
#include <boost/type_traits/is_reference.hpp>
#include <boost/type_traits/is_volatile.hpp>
#include <boost/type_traits/remove_reference.hpp>


namespace boost { namespace egg { namespace details {


    template<class From, class To>
    struct affect_const :
        mpl::eval_if< is_const<From>,
            add_const<To>,
            mpl::identity<To>
        >
    { };


    template<class From, class To>
    struct affect_volatile :
        mpl::eval_if< is_volatile<From>,
            add_volatile<To>,
            mpl::identity<To>
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
        mpl::eval_if< is_reference<From>,
            add_reference<To>,
            mpl::identity<To>
        >
    { };


    template<class From, class To>
    struct affect
    {
        typedef
            typename remove_reference<From>::type
        non_ref_from;

        typedef
            typename affect_reference<From,
                typename affect_cv<non_ref_from, To>::type
            >::type
        type;
    };


} } } // namespace boost::egg::details


#endif
