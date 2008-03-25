#ifndef BOOST_EGG_DETAIL_NULLARY_RESULT_OF_LITTLE_HPP
#define BOOST_EGG_DETAIL_NULLARY_RESULT_OF_LITTLE_HPP


// Boost.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/mpl/eval_if.hpp>
#include <boost/mpl/identity.hpp>
#include <boost/egg/function_fwd.hpp>
#include <boost/egg/detail/has_xxx.hpp>
#include <boost/egg/detail/if_use_default.hpp>
#include <boost/egg/detail/unspecified.hpp>


template<class Function>
struct ERROR_BOOST_EGG_FUNCTION_NON_NULLARY;


namespace boost { namespace egg { namespace details {


    BOOST_EGG_HAS_XXX(nullary_result_type)


    template<class Little, class Function>
    struct extract_nullary_result_of_little :
        if_use_default< typename Little::nullary_result_type,
            ERROR_BOOST_EGG_FUNCTION_NON_NULLARY<Function>,
            typename Little::nullary_result_type
        >
    { };


    template<class Little, class Function = function<Little, unspecified> >
    struct nullary_result_of_little :
        mpl::eval_if< has_nullary_result_type<Little>,
            extract_nullary_result_of_little<Little, Function>,
            mpl::identity< ERROR_BOOST_EGG_FUNCTION_NON_NULLARY<Function> >
        >
    { };


} } }// namespace boost::egg::details


#endif
