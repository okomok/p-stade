#ifndef PSTADE_TOMATO_ATL_CONFIG_HPP
#define PSTADE_TOMATO_ATL_CONFIG_HPP


// PStade.Tomato
//
// Copyright Shunsuke Sogame 2007.
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)


#include <atldef.h> // _ATL_VER


#if !defined(PSTADE_TOMATO_ATL_VER)
    #define PSTADE_TOMATO_ATL_VER _ATL_VER
#endif


#if !defined(PSTADE_TOMATO_ATL_NO_COLLECTIONS)
    #if (_ATL_VER < 0x0700)
        #define PSTADE_TOMATO_ATL_NO_COLLECTIONS
    #endif
#endif


#if !defined(PSTADE_TOMATO_ATL_HAS_OLD_CSIMPLECOLL)
    #if (PSTADE_TOMATO_ATL_VER < 0x0700) // dubious
        #define PSTADE_TOMATO_ATL_HAS_OLD_CSIMPLECOLL
    #endif
#endif


#if !defined(PSTADE_TOMATO_ATL_HAS_OLD_CSIMPLESTRING)
    #if (_MSC_VER < 1310)  // See: <boost/regex/mfc.hpp>
        #define PSTADE_TOMATO_ATL_HAS_OLD_CSIMPLESTRING
    #endif
#endif


#if !defined(PSTADE_TOMATO_ATL_HAS_OLD_CSIMPLECOLL)
    #define PSTADE_TOMATO_ATL_CSIMPLEARRAY_TEMPLATE_PARAMS class T, class TEqual
    #define PSTADE_TOMATO_ATL_CSIMPLEARRAY_TEMPLATE_ARGS   T, TEqual
    #define PSTADE_TOMATO_ATL_CSIMPLEMAP_TEMPLATE_PARAMS   class TKey, class TVal, class TEqual
    #define PSTADE_TOMATO_ATL_CSIMPLEMAP_TEMPLATE_ARGS     TKey, TVal, TEqual
#else
    #define PSTADE_TOMATO_ATL_CSIMPLEARRAY_TEMPLATE_PARAMS class T
    #define PSTADE_TOMATO_ATL_CSIMPLEARRAY_TEMPLATE_ARGS   T
    #define PSTADE_TOMATO_ATL_CSIMPLEMAP_TEMPLATE_PARAMS   class TKey, class TVal
    #define PSTADE_TOMATO_ATL_CSIMPLEMAP_TEMPLATE_ARGS     TKey, TVal
#endif


#if !defined(PSTADE_TOMATO_ATL_HAS_OLD_CSIMPLESTRING)
    #define PSTADE_TOMATO_ATL_CSIMPLESTRINGT_TEMPLATE_PARAMS class BaseType, bool t_bMFCDLL
    #define PSTADE_TOMATO_ATL_CSIMPLESTRINGT_TEMPLATE_ARGS BaseType, t_bMFCDLL 
#else
    #define PSTADE_TOMATO_ATL_CSIMPLESTRINGT_TEMPLATE_PARAMS class BaseType
    #define PSTADE_TOMATO_ATL_CSIMPLESTRINGT_TEMPLATE_ARGS BaseType
#endif


#endif
