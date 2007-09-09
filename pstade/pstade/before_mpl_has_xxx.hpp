#ifndef PSTADE_BEFORE_MPL_HAS_XXX_HPP
#define PSTADE_BEFORE_MPL_HAS_XXX_HPP
#include "./detail/prefix.hpp"


// PStade.Wine
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// Note:
//
// <boost/mpl/has_xxx.hpp> is randomly broken under msvc-7.1/8.0.
// Though it was tried to fix the weird behavior by Boost v1.34,
// it seems still broken; see "../libs/oven/example/newton.cpp".


#include <boost/config.hpp>
#include <boost/detail/workaround.hpp>


// Any Boost library doesn't use BOOST_MPL_HAS_XXX_TRAIT_NAMED_DEF for now.
#if BOOST_WORKAROUND(BOOST_MSVC, BOOST_TESTED_AT(1400))
    #include <boost/mpl/has_xxx.hpp>
    #include <pstade/has_xxx.hpp>
    #undef  BOOST_MPL_HAS_XXX_TRAIT_DEF
    #define BOOST_MPL_HAS_XXX_TRAIT_DEF PSTADE_HAS_TYPE
#endif


#endif
