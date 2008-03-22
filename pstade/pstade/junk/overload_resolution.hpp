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
#include <boost/mpl/begin.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/mpl/deref.hpp>
#include <boost/mpl/distance.hpp>
#include <boost/mpl/equal.hpp>
#include <boost/mpl/int.hpp>
#include <boost/mpl/placeholders.hpp>
#include <boost/egg/detail/is_convertible.hpp>
#include <boost/egg/detail/is_mpl_placeholder_expr.hpp>


namespace boost { namespace egg { namespace details {


    struct is_matched
    {
        template<class Arg, class Param>
        struct apply :
            is_mpl_placeholder_expr< Param,
                mpl::apply1<Param, Arg>,
                is_convertible_<Arg, Param>
            >
        { };

        template<class Arg>
        struct apply<Arg, mpl::_> :
            mpl::true_
        { };
    };


    template<class Sig, class Args>
    struct has_matched_params :
        mpl::equal<
            typename function_types::parameter_types<Sig>::type,
            Args,
            is_matched
        >
    { };


    template<class Sigs, class Args>
    struct overload_resolution
    {
        typedef typename
            mpl::find_if< Sigs, has_matched_params<mpl::_, Args> >::type
        iter_t;

        typedef
            mpl::int_<
                mpl::distance<typename mpl::begin<Sigs>::type, iter_t>::type::value
            >
        index_type;

        typedef typename
            function_types::result_type<typename mpl::deref<iter_t>::type>::type
        target_type;
    };


} } } // namespace boost::egg::details


#endif
