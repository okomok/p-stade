#ifndef PSTADE_OVEN_DETAIL_CONFIG_HPP
#define PSTADE_OVEN_DETAIL_CONFIG_HPP
#include "./prefix.hpp"


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/config.hpp> // BOOST_HAS_THREADS
#include <boost/version.hpp>


#if BOOST_VERSION < 103500
    #define PSTADE_OVEN_BOOST_RANGE_VERSION_1
#endif


#if defined(BOOST_HAS_THREADS) && !defined(PSTADE_OVEN_DISABLE_THREADS)
    #define PSTADE_OVEN_HAS_THREADS
#endif


#endif
