#ifndef BOOST_MICROSOFT_ATL_CONFIG_HPP
#define BOOST_MICROSOFT_ATL_CONFIG_HPP


// Boost.Microsoft
//
// Copyright 2006 Shunsuke Sogame.
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)


#include <atldef.h> // _ATL_VER


#if !defined(BOOST_MICROSOFT_ATL_VER)
    #define BOOST_MICROSOFT_ATL_VER _ATL_VER
#endif


#if !defined(BOOST_MICROSOFT_ATL_HAS_OLD_CSIMPLEARRAY)
    #if (BOOST_MICROSOFT_ATL_VER < 0x0700) // dubious
        #define BOOST_MICROSOFT_ATL_HAS_OLD_CSIMPLEARRAY
    #endif
#endif


#if !defined(BOOST_MICROSOFT_ATL_HAS_OLD_CSIMPLESTRING)
    #if (_MSC_VER < 1310)  // See: <boost/regex/mfc.hpp>
        #define BOOST_MICROSOFT_ATL_HAS_OLD_CSIMPLESTRING
    #endif
#endif


#if !defined(BOOST_MICROSOFT_ATL_HAS_OLD_CSIMPLEARRAY)
    #define BOOST_MICROSOFT_ATL_CSIMPLEARRAY_TEMPLATE_PARAMS class T, class TEqual
    #define BOOST_MICROSOFT_ATL_CSIMPLEARRAY_TEMPLATE_ARGS T, TEqual
#else
    #define BOOST_MICROSOFT_ATL_CSIMPLEARRAY_TEMPLATE_PARAMS class T
    #define BOOST_MICROSOFT_ATL_CSIMPLEARRAY_TEMPLATE_ARGS T
#endif


#if !defined(BOOST_MICROSOFT_ATL_HAS_OLD_CSIMPLESTRING)
    #define BOOST_MICROSOFT_ATL_CSIMPLESTRINGT_TEMPLATE_PARAMS class BaseType, bool t_bMFCDLL
    #define BOOST_MICROSOFT_ATL_CSIMPLESTRINGT_TEMPLATE_ARGS BaseType, t_bMFCDLL 
#else
    #define BOOST_MICROSOFT_ATL_CSIMPLESTRINGT_TEMPLATE_PARAMS class BaseType
    #define BOOST_MICROSOFT_ATL_CSIMPLESTRINGT_TEMPLATE_ARGS BaseType
#endif


#endif
