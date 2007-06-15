#ifndef PSTADE_GRAVY_SDK_SHLWAPI_HPP
#define PSTADE_GRAVY_SDK_SHLWAPI_HPP


// PStade.Gravy
//
// Copyright Shunsuke Sogame 2007.
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)


#include "./config.hpp"


#if !defined(PSTADE_GRAVY_NO_SHLWAPI)

    #if defined(_MSC_VER)
        #pragma comment(lib, "shlwapi.lib")
    #endif

    #include <shlwapi.h>

#endif


#endif
