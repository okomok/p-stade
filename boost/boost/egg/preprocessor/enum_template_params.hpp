#ifndef BOOST_EGG_PP_ENUM_TEMPLATE_PARAMS_HPP
#define BOOST_EGG_PP_ENUM_TEMPLATE_PARAMS_HPP


// Boost.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/preprocessor/control/if.hpp>
#include <boost/preprocessor/facilities/empty.hpp>
#include <boost/preprocessor/facilities/identity.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>


#define BOOST_EGG_PP_ENUM_TEMPLATE_PARAMS(N, A) \
    BOOST_PP_IF(N, BOOST_PP_IDENTITY(template<), BOOST_PP_EMPTY)() \
        BOOST_PP_ENUM_PARAMS(N, A) \
    BOOST_PP_IF(N, BOOST_PP_IDENTITY(>), BOOST_PP_EMPTY)() \
/**/


#endif
