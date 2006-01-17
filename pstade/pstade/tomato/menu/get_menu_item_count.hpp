#pragma once

// Workaround: WinCE doesn't have ::GetMenuItemCount.

#include "../meta/uint.hpp"
#include "../structure/version_initialize.hpp"
#include "../structure/zero_initialize.hpp"

namespace pstade { namespace tomato {


#if !defined(_WIN32_WCE)

	inline int get_menu_item_count(HMENU hMenu)
	{
		return ::GetMenuItemCount(hMenu);
	}

#else

	inline int get_menu_item_count(HMENU hMenu)
	{
		// See: wec400/STANDARDSDK/Mfc/Src/wcealt.cpp

		typedef uint<256> max_item_count;

		MENUITEMINFO mii;
		tomato::version_initialize(zero_initialize(mii));

		int count = 0;
		for (UINT i = 0; i < max_item_count::value; ++i) {
			if (!::GetMenuItemInfo(hMenu, i, TRUE, &mii))
				break;

			++count;
		}

		return count;
	}

#endif // !defined(_WIN32_WCE)


} } // namespace pstade::tomato
