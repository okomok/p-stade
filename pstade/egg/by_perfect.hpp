#ifndef PSTADE_EGG_BY_PERFECT_HPP
#define PSTADE_EGG_BY_PERFECT_HPP
#include "./detail/prefix.hpp"


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/preprocessor/arithmetic/inc.hpp>
#include <pstade/preprocessor.hpp> // PSTADE_PP_SEQ_RANGE
#include "./config.hpp" // PSTADE_EGG_MAX_ARITY
#include "./perfect_strategy.hpp"


#define  PSTADE_EGG_PERFECT_STRATEGY_PARAMS (pstade::egg::by_perfect, PSTADE_PP_SEQ_RANGE(0, BOOST_PP_INC(PSTADE_EGG_MAX_ARITY)))
#include PSTADE_EGG_PERFECT_STRATEGY()


#endif
