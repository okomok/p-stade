#ifndef PSTADE_TOMATO_MENU_GET_MENU_ITEM_ID_HPP
#define PSTADE_TOMATO_MENU_GET_MENU_ITEM_ID_HPP


// PStade.Tomato
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// See:
//
// wec400/STANDARDSDK/Mfc/Src/wcealt.cpp


#include <boost/assert.hpp>
#include <pstade/apple/sdk/windows.hpp>
#include <pstade/require.hpp>
#include "../diet/valid.hpp"
#include "../size_initialize.hpp"


namespace pstade { namespace tomato {


inline
UINT get_menu_item_id(HMENU hMenu, int nPos)
{
    BOOST_ASSERT(diet::valid(hMenu));

#if !defined(_WIN32_WCE)

    return ::GetMenuItemID(hMenu, nPos);

#else

    MENUITEMINFO mii = { 0 }; {
        mii|size_initialized;
        mii.fMask  = MIIM_ID;
    }

    PSTADE_REQUIRE(::GetMenuItemInfo(hMenu, nPos, TRUE, &mii));
    return mii.wID; 

#endif // !defined(_WIN32_WCE)
}


} } // namespace pstade::tomato


#endif
