#ifndef PSTADE_TOMATO_MENU_GET_MENU_ITEM_COUNT_HPP
#define PSTADE_TOMATO_MENU_GET_MENU_ITEM_COUNT_HPP


// PStade.Tomato
//
// Copyright 2006 MB.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// See:
//
// wec400/STANDARDSDK/Mfc/Src/wcealt.cpp


#include <boost/assert.hpp>
#include <boost/microsoft/sdk/windows.hpp>
#include "../diet/valid.hpp"
#include "../meta/uint.hpp"
#include "../require.hpp"
#include "../size_initialize.hpp"
#include "../zero_initialize.hpp"


namespace pstade { namespace tomato {


inline
int get_menu_item_count(HMENU hMenu)
{
	BOOST_ASSERT(diet::valid(hMenu));

#if !defined(_WIN32_WCE)


	return ::GetMenuItemCount(hMenu);


#else


	typedef uint<256> max_item_count;

	MENUITEMINFO mii;
	mii|zero_initialized|size_initialized;

	int count = 0;
	for (UINT i = 0; i < max_item_count::value; ++i) {
		if (!::GetMenuItemInfo(hMenu, i, TRUE, &mii))
			break;

		++count;
	}

	return count;


#endif // !defined(_WIN32_WCE)

}


} } // namespace pstade::tomato


#endif
