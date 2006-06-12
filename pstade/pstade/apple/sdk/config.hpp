#ifndef PSTADE_APPLE_SDK_CONFIG_HPP
#define PSTADE_APPLE_SDK_CONFIG_HPP


// PStade.Apple
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)


#if (_WIN32_IE < 0x0400) || defined(_WIN32_WCE)
    #define PSTADE_APPLE_SDK_NO_SHLWAPI
#endif


#endif
