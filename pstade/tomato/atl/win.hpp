#ifndef PSTADE_TOMATO_ATL_WIN_HPP
#define PSTADE_TOMATO_ATL_WIN_HPP


// PStade.Tomato
//
// Copyright Shunsuke Sogame 2007.
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)


#include "./base.hpp"   // for <atlwin.h>
#include "./config.hpp" // ATL_VER
#include "./module.hpp" // for <atlwin.h> of ATL3


#if (PSTADE_TOMATO_ATL_VER < 0x0700)

    #if defined(__ATLWIN_H__)
        #error <atlwin.h> shall not be included before.
    #endif

    #pragma conform(forScope, off)
    #include <atlwin.h>
    #pragma conform(forScope, on)

#else

    #include <atlwin.h>

#endif // (PSTADE_TOMATO_ATL_VER < 0x0700)


#endif
