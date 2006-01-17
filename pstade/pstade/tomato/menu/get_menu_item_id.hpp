#pragma once

#include "../diagnostic/verify.hpp"
#include "../structure/version_initialize.hpp"
#include "../structure/zero_initialize.hpp"

namespace pstade { namespace tomato {


#if !defined(_WIN32_WCE)

	inline UINT get_menu_item_id(HMENU hMenu, int nPos)
	{
		return ::GetMenuItemID(hMenu, nPos);
	}

#else

	inline UINT get_menu_item_id(HMENU hMenu, int nPos)
	{
		// See: wec400/STANDARDSDK/Mfc/Src/wcealt.cpp

		MENUITEMINFO mii;
		tomato::version_initialize(zero_initialize(mii));
		mii.fMask  = MIIM_ID;

		tomato::api_verify(::GetMenuItemInfo(hMenu, nPos, TRUE, &mii));
		return mii.wID; 
	}

#endif // !defined(_WIN32_WCE)


} } // namespace pstade::tomato
