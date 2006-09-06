#ifndef PSTADE_APPLE_ATL_CONFIG_HPP
#define PSTADE_APPLE_ATL_CONFIG_HPP


// PStade.Apple
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)


#include <atldef.h> // _ATL_VER


#if !defined(PSTADE_APPLE_ATL_VER)
    #define PSTADE_APPLE_ATL_VER _ATL_VER
#endif


#if !defined(PSTADE_APPLE_ATL_HAS_OLD_CSIMPLEARRAY)
    #if (PSTADE_APPLE_ATL_VER < 0x0700) // dubious
        #define PSTADE_APPLE_ATL_HAS_OLD_CSIMPLEARRAY
    #endif
#endif


#if !defined(PSTADE_APPLE_ATL_HAS_OLD_CSIMPLESTRING)
    #if (_MSC_VER < 1310)  // See: <boost/regex/mfc.hpp>
        #define PSTADE_APPLE_ATL_HAS_OLD_CSIMPLESTRING
    #endif
#endif


#if !defined(PSTADE_APPLE_ATL_HAS_OLD_CSIMPLEARRAY)
    #define PSTADE_APPLE_ATL_CSIMPLEARRAY_TEMPLATE_PARAMS class T, class TEqual
    #define PSTADE_APPLE_ATL_CSIMPLEARRAY_TEMPLATE_ARGS T, TEqual
#else
    #define PSTADE_APPLE_ATL_CSIMPLEARRAY_TEMPLATE_PARAMS class T
    #define PSTADE_APPLE_ATL_CSIMPLEARRAY_TEMPLATE_ARGS T
#endif


#if !defined(PSTADE_APPLE_ATL_HAS_OLD_CSIMPLESTRING)
    #define PSTADE_APPLE_ATL_CSIMPLESTRINGT_TEMPLATE_PARAMS class BaseType, bool t_bMFCDLL
    #define PSTADE_APPLE_ATL_CSIMPLESTRINGT_TEMPLATE_ARGS BaseType, t_bMFCDLL 
#else
    #define PSTADE_APPLE_ATL_CSIMPLESTRINGT_TEMPLATE_PARAMS class BaseType
    #define PSTADE_APPLE_ATL_CSIMPLESTRINGT_TEMPLATE_ARGS BaseType
#endif


#endif
