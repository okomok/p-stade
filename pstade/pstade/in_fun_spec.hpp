#ifndef PSTADE_IN_FUN_SPEC_HPP
#define PSTADE_IN_FUN_SPEC_HPP
#include "./detail/prefix.hpp"


// PStade.Wine
//
// Copyright Shunsuke Sogame 2005-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/preprocessor/control/if.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/preprocessor/tuple/eat.hpp>


// Some compilers prefer `(void)` to `()` in function type specialization.
#define PSTADE_VOID_IN_FUN_SPEC void


#define PSTADE_PP_ENUM_PARAMS_IN_FUN_SPEC(N, A) \
    BOOST_PP_IF(N, BOOST_PP_ENUM_PARAMS, PSTADE_VOID_IN_FUN_SPEC BOOST_PP_TUPLE_EAT(2))(N, A) \
/**/


#endif
