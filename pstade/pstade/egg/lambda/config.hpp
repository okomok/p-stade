#ifndef PSTADE_EGG_LAMBDA_CONFIG_HPP
#define PSTADE_EGG_LAMBDA_CONFIG_HPP
#include "../detail/prefix.hpp"


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/version.hpp>


#if !defined(PSTADE_EGG_LAMBDA_FUNCTOR_MAX_ARITY)
    #define PSTADE_EGG_LAMBDA_FUNCTOR_MAX_ARITY 3
#endif


#if !defined(PSTADE_EGG_LAMBDA_BIND_MAX_ARITY)
    #define PSTADE_EGG_LAMBDA_BIND_MAX_ARITY 10
#endif


#if !defined(PSTADE_EGG_LAMBDA_BIND_TARGET_MAX_ARITY)
    #define PSTADE_EGG_LAMBDA_BIND_TARGET_MAX_ARITY 9
#endif


#if BOOST_VERSION >= 103500
    #define PSTADE_EGG_LAMBDA_PERFECT_FUNCTORS
#endif


#endif
