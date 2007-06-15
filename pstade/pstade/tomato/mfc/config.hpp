#ifndef PSTADE_TOMATO_MFC_CONFIG_HPP
#define PSTADE_TOMATO_MFC_CONFIG_HPP


// PStade.Tomato
//
// Copyright Shunsuke Sogame 2007.
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)


#include "./afx.hpp" // _MFC_VER


#if !defined(PSTADE_TOMATO_MFC_VER)
    #define PSTADE_TOMATO_MFC_VER _MFC_VER
#endif


#if !defined(PSTADE_TOMATO_MFC_HAS_LEGACY_STRING)
    #if (_MFC_VER < 0x0700) // dubious
        #define PSTADE_TOMATO_MFC_HAS_LEGACY_STRING
    #endif
#endif


#if !defined(PSTADE_TOMATO_MFC_NO_CPAIR)
    #if (_MFC_VER < 0x0700) // dubious
        #define PSTADE_TOMATO_MFC_NO_CPAIR
    #endif
#endif


// A const collection of old MFC doesn't return const reference.
//
#if !defined(PSTADE_TOMATO_MFC_CONST_COL_RETURNS_NON_REF)
    #if (_MFC_VER < 0x0700) // dubious
        #define PSTADE_TOMATO_MFC_CONST_COL_RETURNS_NON_REF
    #endif
#endif


#endif
