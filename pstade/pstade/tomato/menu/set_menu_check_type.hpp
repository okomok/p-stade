#ifndef PSTADE_TOMATO_MENU_SET_MENU_CHECK_TYPE_HPP
#define PSTADE_TOMATO_MENU_SET_MENU_CHECK_TYPE_HPP


// PStade.Tomato
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/scoped_array.hpp>
#include <pstade/apple/sdk/windows.hpp>
#include <pstade/candy/reset.hpp>
#include <pstade/candy/set.hpp>
#include <pstade/candy/test.hpp>
#include <pstade/require.hpp>
#include <pstade/unused.hpp>
#include "../size_initialize.hpp"
#include "./menu_ref.hpp"


namespace pstade { namespace tomato {


inline
void set_menu_check_type(menu_ref menu, UINT uIndex, bool on)
{
#if !defined(_WIN32_WCE)

    MENUITEMINFO mii = { 0 }; {
        mii|size_initialized;
        mii.fMask = MIIM_TYPE;
        PSTADE_REQUIRE(::GetMenuItemInfo(menu, uIndex, TRUE, &mii));
    }

    if (on == candy::test(mii.fType, MFT_RADIOCHECK))
        return;

    boost::scoped_array<TCHAR> szString;

    if (// The case of MFT_STRING; MFT_STRING == 0, so...
        !candy::test(mii.fType, MFT_BITMAP) &&
        !candy::test(mii.fType, MFT_SEPARATOR) &&
        !candy::test(mii.fType, MFT_OWNERDRAW) // Win32 documentation is broken.
    ) {
        // get the menu_ref string
        szString.reset(new TCHAR[mii.cch + 1]);
        mii.dwTypeData = szString.get();
        ++mii.cch; 
        PSTADE_REQUIRE(::GetMenuItemInfo(menu, uIndex, TRUE, &mii));
    }

    if (on)
        candy::set(mii.fType, MFT_RADIOCHECK);
    else
        candy::reset(mii.fType, MFT_RADIOCHECK);

    PSTADE_REQUIRE(::SetMenuItemInfo(menu, uIndex, TRUE, &mii));

#else

    pstade::unused(menu, uIndex, on);

#endif // !defined(_WIN32_WCE)
}


} } // namespace pstade::tomato


#endif
