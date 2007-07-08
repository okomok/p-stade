#ifndef PSTADE_GRAVY_AUTO_LINK_HPP
#define PSTADE_GRAVY_AUTO_LINK_HPP


// PStade.Gravy
//
// Copyright Shunsuke Sogame 2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/config.hpp>
#include "./sdk/config.hpp"


#if defined(BOOST_MSVC)
    #pragma comment(lib, "comctl32.lib")
    #pragma comment(lib, "comdlg32.lib")
    #pragma comment(lib, "gdi32.lib")
    #pragma comment(lib, "user32.lib")
    #if !defined(PSTADE_GRAVY_NO_SHLWAPI)
        #pragma comment(lib, "shlwapi.lib")
    #endif
#endif


#endif
