#ifndef PSTADE_TOMATO_MENU_GET_MENU_STATE_HPP
#define PSTADE_TOMATO_MENU_GET_MENU_STATE_HPP


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
#include <boost/microsoft/sdk/windows.hpp>
#include <pstade/candy/test.hpp>
#include <pstade/require.hpp>
#include "../diet/valid.hpp"
#include "../size_initialize.hpp"


namespace pstade { namespace tomato {


inline
UINT get_menu_state(HMENU hMenu, UINT uId, UINT uFlags)
{
    BOOST_ASSERT(diet::valid(hMenu));

#if !defined(_WIN32_WCE)


    return ::GetMenuState(hMenu, uId, uFlags);


#else


    MENUITEMINFO mii = { 0 }; {
        mii|size_initialized;
        mii.fMask  = MIIM_STATE;
    }

    if (candy::test(uFlags, MF_BYPOSITION))
        PSTADE_REQUIRE(::GetMenuItemInfo(hMenu, uId, TRUE, &mii));
    else
        PSTADE_REQUIRE(::GetMenuItemInfo(hMenu, uId, FALSE, &mii));

    return mii.fState;


#endif // !defined(_WIN32_WCE)

}


} } // namespace pstade::tomato


#endif
