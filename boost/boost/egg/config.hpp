#ifndef BOOST_EGG_CONFIG_HPP
#define BOOST_EGG_CONFIG_HPP
#include <boost/egg/detail/prefix.hpp>


// Boost.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/config.hpp>
#include <boost/preprocessor/arithmetic/dec.hpp>
#include <boost/version.hpp>
#include <boost/egg/detail/boost_workaround.hpp>


#if !defined(BOOST_EGG_MAX_ARITY)
    #define BOOST_EGG_MAX_ARITY 5
#endif


#if !defined(BOOST_EGG_MAX_LINEAR_ARITY)
    #define BOOST_EGG_MAX_LINEAR_ARITY 10
#endif


#if !defined(BOOST_EGG_PIPABLE_MAX_ARITY)
    #define BOOST_EGG_PIPABLE_MAX_ARITY BOOST_PP_DEC(BOOST_EGG_MAX_LINEAR_ARITY)
#endif


#if !defined(BOOST_EGG_NEST_MAX_LEVEL)
    #define BOOST_EGG_NEST_MAX_LEVEL 5
#endif


#if defined(BOOST_HAS_THREADS) && !defined(BOOST_EGG_DISABLE_THREADS)
    #define BOOST_EGG_HAS_THREADS
#endif


#if (BOOST_VERSION >= 103500) && !defined(BOOST_EGG_DISABLE_FUSIONS)
    #define BOOST_EGG_HAS_FUSIONS
#endif


#if 0 // defined(BOOST_HAS_RVALUE_REFS) && !defined(BOOST_EGG_DISABLE_RVALUE_REFS)
    #define BOOST_EGG_HAS_RVALUE_REFS
#endif


#if BOOST_WORKAROUND(__GNUC__, == 3)
    #define BOOST_EGG_NEEDS_OVERLOADED
#endif


#if BOOST_EGG_MAX_ARITY < 5
    #error BOOST_EGG_MAX_ARITY is too small.
#endif

#if BOOST_EGG_MAX_LINEAR_ARITY < 10
    #error BOOST_EGG_MAX_LINEAR_ARITY is too small.
#endif

#if BOOST_EGG_MAX_LINEAR_ARITY < BOOST_EGG_MAX_ARITY
    #error BOOST_EGG_MAX_ARITY is too large.
#endif


#include <boost/egg/detail/suffix.hpp>
#endif
