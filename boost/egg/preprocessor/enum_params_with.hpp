#ifndef BOOST_EGG_PREPROCESSOR_ENUM_PARAMS_WITH_HPP
#define BOOST_EGG_PREPROCESSOR_ENUM_PARAMS_WITH_HPP


// Boost.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/preprocessor/facilities/intercept.hpp>
#include <boost/preprocessor/repetition/enum_binary_params.hpp>


#define BOOST_EGG_PP_ENUM_PARAMS_WITH(Size, Param, A) \
    BOOST_PP_ENUM_BINARY_PARAMS(Size, Param, A BOOST_PP_INTERCEPT) \
/**/


#endif
