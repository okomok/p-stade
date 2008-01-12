#ifndef BOOST_EGG_DETAIL_USE_BRACE_HPP
#define BOOST_EGG_DETAIL_USE_BRACE_HPP
#include "./prefix.hpp"


// Boost.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/mpl/limits/arity.hpp>
#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/iteration/iterate.hpp>
#include <boost/preprocessor/repetition/enum_binary_params.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/preprocessor/repetition/repeat.hpp>
#include <boost/type.hpp>


#define BOOST_EGG_REPEAT_BRACE_L(N) BOOST_PP_REPEAT(N, BOOST_EGG_REPEAT_BRACE_L_op, ~)
#define BOOST_EGG_REPEAT_BRACE_L_op(Z, N, _) {
#define BOOST_EGG_REPEAT_BRACE_R(N) BOOST_PP_REPEAT(N, BOOST_EGG_REPEAT_BRACE_R_op, ~)
#define BOOST_EGG_REPEAT_BRACE_R_op(Z, N, _) }


#define BOOST_EGG_USE_BRACE() <boost/egg/detail/use_brace_include.hpp>


#endif
