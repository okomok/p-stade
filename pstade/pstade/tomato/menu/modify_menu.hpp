#pragma once

#include <pstade/candy/set.hpp>
#include "./get_menu_item_count.hpp"
#include "./get_menu_item_id.hpp"

namespace pstade { namespace tomato {


#if !defined(_WIN32_WCE)

	inline BOOL modify_menu(HMENU hMenu, UINT uPosition, UINT uFlags, UINT uIDNewItem = 0, LPCTSTR lpNewItem = NULL)
	{
		return ::ModifyMenu(hMenu, uPosition, uFlags, uIDNewItem, lpNewItem);
	}

#else

	inline BOOL modify_menu(HMENU hMenu, UINT uPosition, UINT uFlags, UINT uIDNewItem = 0, LPCTSTR lpNewItem = NULL)
	{
		// See: wec400/STANDARDSDK/Mfc/Src/wcealt.cpp

		// Handle MF_BYCOMMAND case; MF_BYCOMMAND is 0
		if ((uFlags & MF_BYPOSITION) != MF_BYPOSITION) {
			int count = tomato::get_menu_item_count(hMenu);
			int pos = 0;

			while (uPosition != tomato::get_menu_item_id(hMenu, pos) && (pos < count))
				++pos;

			ATLASSERT(pos < count);

			uPosition = pos;
			candy::set(uFlags, MF_BYPOSITION);
		}

		if (!::DeleteMenu(hMenu, uPosition, uFlags))
			return FALSE;

		return ::InsertMenu(hMenu, uPosition, uFlags, uIDNewItem, lpNewItem);
	}

#endif // !defined(_WIN32_WCE)


} } // namespace pstade::tomato
