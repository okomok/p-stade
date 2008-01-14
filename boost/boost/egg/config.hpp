#ifndef BOOST_EGG_CONFIG_HPP
#define BOOST_EGG_CONFIG_HPP
#include "./detail/prefix.hpp"


// Boost.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/config.hpp> // BOOST_HAS_THREADS


#if !defined(BOOST_EGG_MAX_ARITY)
    #define BOOST_EGG_MAX_ARITY 5
#endif


#if !defined(BOOST_EGG_MAX_LINEAR_ARITY)
    #define BOOST_EGG_MAX_LINEAR_ARITY 10
#endif


#if defined(BOOST_HAS_THREADS) && !defined(BOOST_EGG_DISABLE_THREADS)
    #define BOOST_EGG_HAS_THREADS
#endif


#if BOOST_EGG_MAX_ARITY < 5
    #error BOOST_EGG_MAX_ARITY is too small.
#endif
#if BOOST_EGG_MAX_LINEAR_ARITY < 10
    #error BOOST_EGG_MAX_LINEAR_ARITY is too small.
#endif


#endif
