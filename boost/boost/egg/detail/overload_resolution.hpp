#ifndef BOOST_EGG_DETAIL_OVERLOAD_RESOLUTION_HPP
#define BOOST_EGG_DETAIL_OVERLOAD_RESOLUTION_HPP


// Boost.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/function_types/parameter_types.hpp>
#include <boost/function_types/result_type.hpp>
#include <boost/mpl/apply.hpp>
#include <boost/mpl/assert.hpp>
#include <boost/mpl/begin.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/mpl/distance.hpp>
#include <boost/mpl/end.hpp>
#include <boost/mpl/eval_if.hpp>
#include <boost/mpl/empty_sequence.hpp>
#include <boost/mpl/equal.hpp>
#include <boost/mpl/identity.hpp>
#include <boost/mpl/int.hpp>
#include <boost/mpl/placeholders.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/type_traits/remove_cv.hpp>
#include <boost/egg/result_of.hpp>
#include <boost/egg/detail/boost_use_default_fwd.hpp>
#include <boost/egg/detail/is_convertible.hpp>
#include <boost/egg/detail/is_mpl_placeholder_expr.hpp>
#include <boost/egg/detail/maybe_find.hpp>
#include <boost/egg/detail/well_formed.hpp>


namespace boost { namespace egg { namespace details {


    struct is_matched
    {
        template<class Arg, class Param>
        struct apply :
            mpl::eval_if< is_mpl_placeholder_expr<Param>,
                mpl::apply1<Param, Arg>,
                is_convertible_<Arg, Param>
            >
        { };

        template<class Arg>
        struct apply<Arg, mpl::_> :
            mpl::true_
        { };

        template<class Arg>
        struct apply<Arg, mpl::_1>;
    };


    template<class FunCall, class Args>
    struct has_matched_params :
        mpl::equal<
            typename remove_cv<Args>::type, // MPL needs this.
            typename function_types::parameter_types<FunCall>::type,
            is_matched
        >
    { };


    template<class FunCalls, class Args>
    struct overload_resolution_index
    {
        typedef typename
            mpl::find_if< FunCalls, has_matched_params<mpl::_, Args> >::type
        iter_t;

        BOOST_MPL_ASSERT_NOT((is_same<iter_t, typename mpl::end<FunCalls>::type>));

        typedef
            mpl::int_<
                mpl::distance<typename mpl::begin<FunCalls>::type, iter_t>::type::value
            >
        type;
    };


    template<class Maybe>
    struct overload_target :
        function_types::result_type<
            typename from_just<Maybe>::type
        >
    { };


    template<class FunCalls, class Args>
    struct overload_resolution
    {
        typedef typename
            maybe_find< FunCalls, has_matched_params<mpl::_, Args> >::type
        maybe_t;

        // by_perfect instantiates all the possible declaration,
        // so that it sometimes fails to find the target function.
        typedef typename
            mpl::eval_if< is_just<maybe_t>,
                overload_target<maybe_t>,
                mpl::identity<well_formed> // dummy in case of no targets found.
            >::type
        type;
    };


    template<class FunCalls>
    struct nullary_result_of_overload_resolution :
        result_of_<
            typename overload_resolution<FunCalls, mpl::empty_sequence>::type()
        >
    { };


} } } // namespace boost::egg::details


#endif
