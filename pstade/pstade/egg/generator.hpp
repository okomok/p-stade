#ifndef PSTADE_EGG_GENERATOR_HPP
#define PSTADE_EGG_GENERATOR_HPP
#include "./detail/prefix.hpp"


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/mpl/and.hpp>
#include <boost/mpl/apply.hpp>
#include <boost/mpl/eval_if.hpp>
#include <boost/mpl/identity.hpp>
#include <boost/type_traits/is_same.hpp>
#include <pstade/apple/boost/reference_wrapper_fwd.hpp>
#include <pstade/pass_by.hpp>
#include "./by_perfect.hpp"
#include "./detail/little_generator.hpp"
#include "./detail/mpl_placeholders.hpp" // inclusion guaranteed
#include "./detail/unspecified.hpp"


struct PSTADE_EGG_ERROR_GENERATOR_MISSING_ARGUMENT;


namespace pstade { namespace egg {


    template<
        class Expr,
        class Strategy      = by_perfect,
        class Construct     = boost::use_default,
        class NullaryResult = boost::use_default
    >
    struct generator
    {
        typedef
            function<detail::little_generator<Expr, Strategy, Construct, NullaryResult>, Strategy>
        type;
    };

    #define PSTADE_EGG_GENERATOR() {{}}


    template<
        class A, class Deducer,
        class Default = unspecified // = PSTADE_EGG_ERROR_GENERATOR_MISSING_ARGUMENT
    >
    struct deduce :
        boost::mpl::eval_if< boost::is_same<A, void>,
            boost::mpl::eval_if< boost::is_same<Default, unspecified>,
                boost::mpl::identity<PSTADE_EGG_ERROR_GENERATOR_MISSING_ARGUMENT>,
                boost::mpl::identity<Default>
            >,
            boost::mpl::apply1<Deducer, A>
        >
    { };


    struct as_ref
    {
        template<class A>
        struct apply
        {
            typedef A& type;
        };
    };

    struct as_cref
    {
        template<class A>
        struct apply
        {
            typedef A const& type;
        };
    };

    struct as_value
    {
        template<class A>
        struct apply :
            pass_by_value<A>
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
            pass_by_value<A>
        { };

        template<class T>
        struct apply< boost::reference_wrapper<T> >
        {
            typedef T& type;
        };

        template<class T>
        struct apply< boost::reference_wrapper<T> const >
        {
            typedef T& type;
        };
    };


} } // namespace pstade::egg


#include "./detail/suffix.hpp"
#endif
