#ifndef PSTADE_GRAVY_DETAIL_MENUITEMINFO_SIZE_V400_HPP
#define PSTADE_GRAVY_DETAIL_MENUITEMINFO_SIZE_V400_HPP


// PStade.Gravy
//
// Copyright Shunsuke Sogame 2007.
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)


#include "../sdk/windows.hpp" // WINVER, LPBYTE


#if (WINVER >= 0x0500)

    #define PSTADE_GRAVY_MII_SIZEOF_STRUCT(structname, member) \
        (((int)((LPBYTE)(&((structname*)0)->member) - ((LPBYTE)((structname*)0)))) + sizeof(((structname*)0)->member))

    #define PSTADE_GRAVY_MENUITEMINFO_SIZE_V400A  PSTADE_GRAVY_MII_SIZEOF_STRUCT(MENUITEMINFOA, cch)
    #define PSTADE_GRAVY_MENUITEMINFO_SIZE_V400W  PSTADE_GRAVY_MII_SIZEOF_STRUCT(MENUITEMINFOW, cch)

    #if defined(UNICODE)
        #define PSTADE_GRAVY_MENUITEMINFO_SIZE_V400 PSTADE_GRAVY_MENUITEMINFO_SIZE_V400W
    #else
        #define PSTADE_GRAVY_MENUITEMINFO_SIZE_V400 PSTADE_GRAVY_MENUITEMINFO_SIZE_V400A
    #endif

#endif // (WINVER >= 0x0500)


#endif
