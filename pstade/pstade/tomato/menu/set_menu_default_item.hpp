#pragma once

#include <pstade/unused.hpp>

namespace pstade { namespace tomato {


#if !defined(_WIN32_WCE)

	inline BOOL set_menu_default_item(HMENU hMenu, UINT uItem = static_cast<UINT>(-1),  BOOL bByPosition = FALSE)
	{
		return ::SetMenuDefaultItem(hMenu, uItem, integral_cast<UINT>(bByPosition));
	}

#else

	inline BOOL set_menu_default_item(HMENU hMenu, UINT uItem = static_cast<UINT>(-1),  BOOL bByPosition = FALSE)
	{
		pstade::unused(hMenu, uItem, bByPosition);
		// what can I do :^)
		return TRUE;
	}

#endif // !defined(_WIN32_WCE)


} } // namespace pstade::tomato
