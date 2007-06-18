#ifndef PSTADE_GRAVY_SDK_WINDOWS_HPP
#define PSTADE_GRAVY_SDK_WINDOWS_HPP


// PStade.Gravy
//
// Copyright Shunsuke Sogame 2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#if !defined(PSTADE_GRAVY_NEVER_INCLUDE_SDK_WINDOWS_H) // for MFC
    #include <windows.h>
#endif


#if defined(_MSC_VER)
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
