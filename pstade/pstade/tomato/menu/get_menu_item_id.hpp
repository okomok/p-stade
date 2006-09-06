#ifndef PSTADE_TOMATO_MENU_GET_MENU_ITEM_ID_HPP
#define PSTADE_TOMATO_MENU_GET_MENU_ITEM_ID_HPP


// PStade.Tomato
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// See:
//
// wec400/STANDARDSDK/Mfc/Src/wcealt.cpp


#include <pstade/apple/sdk/windows.hpp>
#include <pstade/require.hpp>
#include "../size_initialize.hpp"
#include "./menu_ref.hpp"


namespace pstade { namespace tomato {


inline
UINT get_menu_item_id(menu_ref menu, int nPos)
{
#if !defined(_WIN32_WCE)

    return ::GetMenuItemID(menu, nPos);

#else

    MENUITEMINFO mii = { 0 }; {
        mii|size_initialized;
        mii.fMask  = MIIM_ID;
    }

    PSTADE_REQUIRE(::GetMenuItemInfo(menu, nPos, TRUE, &mii));
    return mii.wID; 

#endif // !defined(_WIN32_WCE)
}


} } // namespace pstade::tomato


#endif
