#ifndef BOOST_EGG_CONST_OVERLOADED_HPP
#define BOOST_EGG_CONST_OVERLOADED_HPP


// Boost.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


//  Copyright 2004 Eric Niebler. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)


// What:
//
// GCC3.4.4 cannot order overloadings of non-const-reference and const-reference
// if it has explicit template arguments.
// So disable the non-const-reference overloading in the case of const-reference.
//
// See: http://tinyurl.com/yhqedd
//
// comp.lang.c++.moderated
// "Forwarding Function Template Resolution and Explicit Template Argument"
//
// After all, GCC overload-resolution is broken with explicit template argument.
// We sooner or later need 'ARRAY_OVERLOADED', too.


#include <boost/mpl/or.hpp>
#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/preprocessor/seq/enum.hpp>
#include <boost/type_traits/is_const.hpp>
#include <boost/egg/detail/enable_if.hpp> // disable_if
#include <boost/egg/detail/boost_workaround.hpp>
#include <boost/egg/detail/pp_enum_params_with.hpp>


// This macro can't always be turned on; especially under VC++.
#if BOOST_WORKAROUND(__GNUC__, == 3) || BOOST_WORKAROUND(__EDG_VERSION__, BOOST_TESTED_AT(306))
    #define BOOST_EGG_CONST_OVERLOADED_REQUIRED
#endif


#if defined(BOOST_EGG_CONST_OVERLOADED_REQUIRED)

    #define BOOST_EGG_CONST_OVERLOADED(T) \
        , typename boost::egg::details::disable_if< \
            boost::is_const<T> \
        >::type = 0 \
    /**/

    #define BOOST_EGG_CONST_OVERLOADED_SEQ(Ts) \
        , typename boost::egg::details::disable_if< \
            boost::egg::details::contains_const<BOOST_PP_SEQ_ENUM(Ts)> \
        >::type = 0 \
    /**/

#else

    #define BOOST_EGG_CONST_OVERLOADED(T)
    #define BOOST_EGG_CONST_OVERLOADED_SEQ(Ts)

#endif


namespace boost { namespace egg { namespace details {


    template<BOOST_PP_ENUM_PARAMS(10, class T)>
    struct or10 :
        mpl::or_<
            mpl::or_<T0, T1, T2, T3, T4>,
            mpl::or_<T5, T6, T7, T8, T9>
        >
    { };


    template<BOOST_EGG_PP_ENUM_PARAMS_WITH(10, class T, = void)>
    struct contains_const :
        or10< BOOST_EGG_PP_ENUM_PARAMS_WITH(10, is_const<T, >) >
    { };


} } } // namespace boost::egg::details


#endif
