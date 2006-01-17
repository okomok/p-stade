#pragma once

#include <pstade/candy/test.hpp>
#include "../diagnostic/verify.hpp"
#include "../structure/version_initialize.hpp"
#include "../structure/zero_initialize.hpp"

namespace pstade { namespace tomato {


#if !defined(_WIN32_WCE)

	inline UINT get_menu_state(HMENU hMenu, UINT uId, UINT uFlags)
	{
		return ::GetMenuState(hMenu, uId, uFlags);
	}

#else

	inline UINT get_menu_state(HMENU hMenu, UINT uId, UINT uFlags)
	{
		// See: wec400/STANDARDSDK/Mfc/Src/wcealt.cpp

		MENUITEMINFO mii;
		tomato::version_initialize(tomato::zero_initialize(mii));
		mii.fMask  = MIIM_STATE;

		if (candy::test(uFlags, MF_BYPOSITION))
			tomato::api_verify(::GetMenuItemInfo(hMenu, uId, TRUE, &mii));
		else
			tomato::api_verify(::GetMenuItemInfo(hMenu, uId, FALSE, &mii));

		return mii.fState;
	}

#endif // !defined(_WIN32_WCE)


} } // namespace pstade::tomato
