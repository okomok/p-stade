#ifndef BOOST_EGG_BLL_CONFIG_HPP
#define BOOST_EGG_BLL_CONFIG_HPP
#include "../detail/prefix.hpp"


// Boost.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/version.hpp>


#if !defined(BOOST_EGG_BLL_FUNCTOR_MAX_ARITY)
    #define BOOST_EGG_BLL_FUNCTOR_MAX_ARITY 3
#endif


#if !defined(BOOST_EGG_BLL_BIND_MAX_ARITY)
    #define BOOST_EGG_BLL_BIND_MAX_ARITY 10
#endif


#if !defined(BOOST_EGG_BLL_BIND_TARGET_MAX_ARITY)
    #define BOOST_EGG_BLL_BIND_TARGET_MAX_ARITY 9
#endif


#if BOOST_VERSION >= 103500
    #define BOOST_EGG_BLL_PERFECT_FUNCTORS
#endif


#endif
