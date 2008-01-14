#ifndef PSTADE_EGG_DETAIL_USE_BRACE_HPP
#define PSTADE_EGG_DETAIL_USE_BRACE_HPP
#include "./prefix.hpp"


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/mpl/limits/arity.hpp>
#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/iteration/iterate.hpp>
#include <boost/preprocessor/repetition/enum_binary_params.hpp>
#include <boost/preprocessor/repetition/enum_trailing_params.hpp>
#include <boost/preprocessor/repetition/repeat.hpp>
#include "../forward.hpp"


#define PSTADE_EGG_REPEAT_BRACE_L(N) BOOST_PP_REPEAT(N, PSTADE_EGG_REPEAT_BRACE_L_op, ~)
#define PSTADE_EGG_REPEAT_BRACE_L_op(Z, N, _) {
#define PSTADE_EGG_REPEAT_BRACE_R(N) BOOST_PP_REPEAT(N, PSTADE_EGG_REPEAT_BRACE_R_op, ~)
#define PSTADE_EGG_REPEAT_BRACE_R_op(Z, N, _) }


#define PSTADE_EGG_USE_BRACE() <pstade/egg/detail/use_brace_include.hpp>


#endif
