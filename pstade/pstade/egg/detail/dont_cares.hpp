#ifndef PSTADE_EGG_DETAIL_DONT_CARES_HPP
#define PSTADE_EGG_DETAIL_DONT_CARES_HPP
#include "./prefix.hpp"


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/preprocessor/facilities/intercept.hpp>
#include <boost/preprocessor/repetition/enum_binary_params.hpp>
#include <pstade/dont_care.hpp>
#include <pstade/pod_constant.hpp>
#include "../config.hpp" // PSTADE_EGG_MAX_LINEAR_ARITY


#define PSTADE_EGG_DONT_CARES() \
    BOOST_PP_ENUM_BINARY_PARAMS(PSTADE_EGG_MAX_LINEAR_ARITY, pstade::dont_care BOOST_PP_INTERCEPT, = 0 BOOST_PP_INTERCEPT) \
/**/


#endif
