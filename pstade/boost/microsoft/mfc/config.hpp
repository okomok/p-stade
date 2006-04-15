#ifndef BOOST_MICROSOFT_MFC_CONFIG_HPP
#define BOOST_MICROSOFT_MFC_CONFIG_HPP


// Boost.Microsoft
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)


#include <afx.h> // _MFC_VER


#if !defined(BOOST_MICROSOFT_MFC_VER)
    #define BOOST_MICROSOFT_MFC_VER _MFC_VER
#endif


#if !defined(BOOST_MICROSOFT_MFC_HAS_LEGACY_STRING)
    #if (_MFC_VER < 0x0700) // dubious
        #define BOOST_MICROSOFT_MFC_HAS_LEGACY_STRING
    #endif
#endif


#endif
