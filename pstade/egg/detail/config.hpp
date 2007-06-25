#ifndef PSTADE_EGG_DETAIL_CONFIG_HPP
#define PSTADE_EGG_DETAIL_CONFIG_HPP
#include "./prefix.hpp"


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/config.hpp>
#include <boost/detail/workaround.hpp>


#if !defined(PSTADE_EGG_MAX_ARITY)
    #define PSTADE_EGG_MAX_ARITY 5
#endif


// The old result_of implementation can't work with a pod class on msvc.
#if BOOST_WORKAROUND(BOOST_MSVC, BOOST_TESTED_AT(1400)) && (BOOST_VERSION < 103500)
    #define PSTADE_EGG_RESULT_OF_CANT_WORK_WITH_TEMPLATE_POD
#endif


// msvc can't static-initialize a reference bound to static-storage.
#if BOOST_WORKAROUND(BOOST_MSVC, BOOST_TESTED_AT(1400))
    #define PSTADE_EGG_NO_STATIC_INITIALIZATION
#endif


#if defined(PSTADE_EGG_RESULT_OF_CANT_WORK_WITH_TEMPLATE_POD) || defined(PSTADE_EGG_NO_STATIC_INITIALIZATION)
    #define PSTADE_EGG_POD_FUNCTION_IN_VAIN
#endif


#endif
