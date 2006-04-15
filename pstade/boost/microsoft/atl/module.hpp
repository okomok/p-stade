#ifndef BOOST_MICROSOFT_ATL_MODULE_HPP
#define BOOST_MICROSOFT_ATL_MODULE_HPP


// Boost.Microsoft
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)


#if !defined(BOOST_MICROSOFT_ATL_MODULE_TYPE)
    #error BOOST_MICROSOFT_ATL_MODULE_TYPE must be defined first
#endif


// That order-dependency means '_Module' type is the very "macro".
//
extern BOOST_MICROSOFT_ATL_MODULE_TYPE _Module;


#endif
