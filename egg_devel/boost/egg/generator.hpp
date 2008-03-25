#ifndef BOOST_EGG_GENERATOR_HPP
#define BOOST_EGG_GENERATOR_HPP
#include <boost/egg/detail/prefix.hpp>


// Boost.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/mpl/and.hpp>
#include <boost/mpl/apply.hpp>
#include <boost/mpl/eval_if.hpp>
#include <boost/mpl/identity.hpp>
#include <boost/mpl/placeholders.hpp> // inclusion guaranteed
#include <boost/type_traits/is_same.hpp>
#include <boost/egg/by_perfect.hpp>
#include <boost/egg/detail/boost_reference_wrapper_fwd.hpp>
#include <boost/egg/detail/little_generator.hpp>
#include <boost/egg/detail/pass_by_value.hpp>
#include <boost/egg/detail/unspecified.hpp>


struct ERROR_BOOST_EGG_GENERATOR_MISSING_ARGUMENT;


namespace boost { namespace egg {


    // Even if using `supply_n`, NullaryResult is needed;
    // consider `foo< metafun<_1> >` where `metafun<void>::type` is ill-formed.

    template<
        class Expr,
        class Strategy      = by_perfect,
        class Construct     = use_default,
        class NullaryResult = use_default
    >
    struct generator
    {
        typedef
            function<details::little_generator<Expr, Strategy, Construct, NullaryResult>, Strategy>
        type;
    };

    #define BOOST_EGG_GENERATOR() {{}}


    template<
        class A, class Deducer,
        class Default = unspecified // = ERROR_BOOST_EGG_GENERATOR_MISSING_ARGUMENT
    >
    struct deduce :
        mpl::eval_if< is_same<A, void>,
            mpl::eval_if< is_same<Default, unspecified>,
                mpl::identity<ERROR_BOOST_EGG_GENERATOR_MISSING_ARGUMENT>,
                mpl::identity<Default>
            >,
            mpl::apply1<Deducer, A>
        >
    { };


    struct as_ref
    {
        template<class A>
        struct apply
        {
            typedef A &type;
        };
    };

    struct as_cref
    {
        template<class A>
        struct apply
        {
            typedef A const &type;
        };
    };

    struct as_value
    {
        template<class A>
        struct apply :
            details::pass_by_value<A>
        { };
    };

    struct as_qualified
    {
        template<class A>
        struct apply
        {
            typedef A type;
        };
    };

    struct as_wrapped_ref
    {
        template<class A>
        struct apply :
            details::pass_by_value<A>
        { };

        template<class T>
        struct apply< reference_wrapper<T> >
        {
            typedef T &type;
        };

        template<class T>
        struct apply< reference_wrapper<T> const >
        {
            typedef T &type;
        };
    };


} } // namespace boost::egg


#include <boost/egg/detail/suffix.hpp>
#endif
