#ifndef BOOST_EGG_TUPLE_CONFIG_HPP
#define BOOST_EGG_TUPLE_CONFIG_HPP
#include "../detail/prefix.hpp"


// Boost.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/version.hpp>


#if !defined(BOOST_EGG_TUPLE_MAX_SIZE)
    #define BOOST_EGG_TUPLE_MAX_SIZE 10
#endif


#if BOOST_VERSION >= 103500
    #define BOOST_EGG_TUPLE_SUPPORTS_FUSION
#endif


#endif
