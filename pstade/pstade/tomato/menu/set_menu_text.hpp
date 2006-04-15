#ifndef PSTADE_TOMATO_MENU_SET_MENU_TEXT_HPP
#define PSTADE_TOMATO_MENU_SET_MENU_TEXT_HPP


// PStade.Tomato
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/assert.hpp>
#include <boost/microsoft/sdk/tchar.hpp>
#include <boost/microsoft/sdk/windows.hpp>
#include <pstade/require.hpp>
#include "../diet/valid.hpp"
#include "../size_initialize.hpp"
#include "../zero_initialize.hpp"
#include "./get_menu_state.hpp"
#include "./mf_bitmap.hpp"
#include "./modify_menu.hpp"


namespace pstade { namespace tomato {


inline
void set_menu_text(HMENU hMenu, UINT uIndex, const TCHAR *pszText)
{
	BOOST_ASSERT(diet::valid(hMenu));
	BOOST_ASSERT(diet::valid(pszText));

	// get current menu state so it doesn't change
	UINT uState = tomato::get_menu_state(hMenu, uIndex, MF_BYPOSITION);
	candy::remove(uState, tomato::mf_bitmap::value | MF_OWNERDRAW | MF_SEPARATOR);

	// set menu text
	MENUITEMINFO mii; {
		mii|zero_initialized|size_initialized;
		mii.fMask = MIIM_ID;
		PSTADE_REQUIRE(::GetMenuItemInfo(hMenu, uIndex, TRUE, &mii));
	}

	PSTADE_REQUIRE(tomato::modify_menu(hMenu, uIndex, MF_BYPOSITION |
		MF_STRING | uState, mii.wID, pszText));
}



} } // namespace pstade::tomato


#endif
