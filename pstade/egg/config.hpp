#ifndef PSTADE_EGG_CONFIG_HPP
#define PSTADE_EGG_CONFIG_HPP
#include "./detail/prefix.hpp"


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/config.hpp> // BOOST_HAS_THREADS
#include <boost/version.hpp>


#if !defined(PSTADE_EGG_MAX_ARITY)
    #define PSTADE_EGG_MAX_ARITY 5
#endif


#if !defined(PSTADE_EGG_FLAT_MAX_ARITY)
    #define PSTADE_EGG_FLAT_MAX_ARITY 10
#endif


#if BOOST_VERSION >= 103500
    #define PSTADE_EGG_SUPPORTS_FUSION_SEQUENCE
    #define PSTADE_EGG_PERFECT_LAMBDA_FUNCTORS
#endif


#if defined(BOOST_HAS_THREADS) && !defined(PSTADE_EGG_DISABLE_THREADS)
    #define PSTADE_EGG_HAS_THREADS
#endif


#endif
