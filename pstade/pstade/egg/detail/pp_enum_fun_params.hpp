#ifndef PSTADE_EGG_DETAIL_PP_ENUM_FUN_PARAMS_HPP
#define PSTADE_EGG_DETAIL_PP_ENUM_FUN_PARAMS_HPP
#include "./prefix.hpp"


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/preprocessor/control/if.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/preprocessor/tuple/eat.hpp>


// Some compilers seem to prefer `(void)` to `()` in template specialization.

#define PSTADE_EGG_PP_ENUM_FUN_PARAMS(N, A) \
    BOOST_PP_IF(N, BOOST_PP_ENUM_PARAMS, void BOOST_PP_TUPLE_EAT(2))(N, A) \
/**/


#endif
