#ifndef PSTADE_TOMATO_MENU_SET_MENU_TEXT_HPP
#define PSTADE_TOMATO_MENU_SET_MENU_TEXT_HPP


// PStade.Tomato
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/apple/sdk/tchar.hpp>
#include <pstade/apple/sdk/windows.hpp>
#include <pstade/require.hpp>
#include "../c_str.hpp"
#include "../size_initialize.hpp"
#include "./get_menu_state.hpp"
#include "./menu_ref.hpp"
#include "./mf_bitmap.hpp"
#include "./modify_menu.hpp"


namespace pstade { namespace tomato {


template< class CStringizable > inline
void set_menu_text(menu_ref menu, UINT uIndex, CStringizable const& text)
{
    // get current menu_ref state so it doesn't change
    UINT uState = tomato::get_menu_state(menu, uIndex, MF_BYPOSITION);
    candy::remove(uState, mf_bitmap::value | MF_OWNERDRAW | MF_SEPARATOR);

    // set menu_ref text
    MENUITEMINFO mii = { 0 }; {
        mii|size_initialized;
        mii.fMask = MIIM_ID;
        PSTADE_REQUIRE(::GetMenuItemInfo(menu, uIndex, TRUE, &mii));
    }

    PSTADE_REQUIRE(tomato::modify_menu(menu, uIndex, MF_BYPOSITION |
        MF_STRING | uState, mii.wID, tomato::c_str(text))
    );
}



} } // namespace pstade::tomato


#endif
