#ifndef PSTADE_APPLE_SDK_WINDOWS_HPP
#define PSTADE_APPLE_SDK_WINDOWS_HPP


// PStade.Apple
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)


#if !defined(PSTADE_APPLE_SDK_WINDOWS_NEVER_INCLUDE) // for MFC
    #include <windows.h>
#endif


#include <boost/config.hpp>

#if defined(BOOST_MSVC)
    #pragma comment(lib, "kernel32.lib")
    #pragma comment(lib, "user32.lib")
    #pragma comment(lib, "gdi32.lib")
    #pragma comment(lib, "winspool.lib")
    #pragma comment(lib, "comdlg32.lib")
    #pragma comment(lib, "advapi32.lib")
    #pragma comment(lib, "shell32.lib")
    #pragma comment(lib, "ole32.lib")
    #pragma comment(lib, "oleaut32.lib")
    #pragma comment(lib, "uuid.lib")
#endif


#endif
