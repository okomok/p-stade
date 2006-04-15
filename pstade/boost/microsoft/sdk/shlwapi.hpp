#ifndef BOOST_MICROSOFT_SDK_SHLWAPI_HPP
#define BOOST_MICROSOFT_SDK_SHLWAPI_HPP


// Boost.Microsoft
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/config.hpp>
#include <boost/microsoft/sdk/config.hpp>


#if !defined(BOOST_MICROSOFT_SDK_NO_SHLWAPI)

    #include <boost/config.hpp>
    #include <boost/detail/workaround.hpp>

    #if defined(BOOST_MSVC)
        #pragma comment(lib, "shlwapi.lib")
    #endif

    #include <shlwapi.h>

#endif


#endif
