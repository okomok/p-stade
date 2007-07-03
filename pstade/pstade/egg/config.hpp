#ifndef PSTADE_EGG_CONFIG_HPP
#define PSTADE_EGG_CONFIG_HPP
#include "./detail/prefix.hpp"


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/config.hpp>
#include <boost/detail/workaround.hpp>
#include <boost/version.hpp>


#if !defined(PSTADE_EGG_MAX_ARITY)
    #define PSTADE_EGG_MAX_ARITY 5
#endif


#if !defined(PSTADE_EGG_FUSE_MAX_ARITY)
    #define PSTADE_EGG_FUSE_MAX_ARITY 10 // follows 'boost::tuple'.
#endif


// msvc optimizers can static-initialize, though.
#if BOOST_WORKAROUND(BOOST_MSVC, BOOST_TESTED_AT(1400))
    #define PSTADE_EGG_NO_STATIC_INITIALIZATION
#endif


#if defined(BOOST_MSVC) && defined(_MSC_FULL_VER) && (_MSC_FULL_VER >=140050215)
    #define PSTADE_EGG_HAS_IS_POD
#endif


#endif
