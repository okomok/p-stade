#ifndef BOOST_EGG_DETAIL_CONST_OVERLOADED_HPP
#define BOOST_EGG_DETAIL_CONST_OVERLOADED_HPP


// Boost.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// What:
//
// See "./const_overloaded1.hpp"


#include <boost/egg/detail/const_overloaded1.hpp>


#if defined(BOOST_EGG_CONST_OVERLOADED_REQUIRED)

    #include <boost/preprocessor/repetition/enum_params.hpp>
    #include <boost/type_traits/is_const.hpp>
    #include <boost/egg/preprocessor/enum_params_with.hpp>
    #include <boost/egg/detail/enable_if.hpp> // disable_if_
    #include <boost/egg/detail/or10.hpp>

    #define BOOST_EGG_CONST_OVERLOADED(N, T) \
        , typename boost::egg::disable_if_< \
            boost::egg::details::exists_const<BOOST_PP_ENUM_PARAMS(N, T)> \
        >::type = 0 \
    /**/

    namespace boost { namespace egg { namespace details {

        template<BOOST_EGG_PP_ENUM_PARAMS_WITH(10, class T, = void)>
        struct exists_const :
            or10< BOOST_EGG_PP_ENUM_PARAMS_WITH(5, is_const<T, >) >
        { };

    } } } // namespace boost::egg::details

#else

    #define BOOST_EGG_CONST_OVERLOADED(N, T)

#endif


#endif
