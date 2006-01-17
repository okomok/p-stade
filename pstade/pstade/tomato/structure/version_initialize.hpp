#pragma once

// Reason:
//   We should make wrappers for all the structures if possible.
//   But, it is impossible.
//   It is better to forget such wrappers and remember the following.

#include <pstade/overload.hpp>

#if (WINVER >= 0x0500)
	#include <atluser.h>
#endif // (WINVER >= 0x0500)

namespace pstade { namespace tomato {


template< class T > inline
T& version_initialize(T& x)
{
	return pstade_tomato_version_initialize(x, overload());
}


} } // namespace pstade::tomato


// default
template< class T > inline
T& pstade_tomato_version_initialize(T& x, ...)
{
	x.cbSize = sizeof(T);
	return x;
}


inline MENUITEMINFO& pstade_tomato_version_initialize(MENUITEMINFO& mii, pstade::overload)
{
	// See: WTL7.5::CMenuItemInfo

	mii.cbSize = sizeof(MENUITEMINFO);

#if (WINVER >= 0x0500)
	// adjust struct size if running on older version of Windows
	if (::AtlIsOldWindows())
	{
		ATLASSERT(mii.cbSize > MENUITEMINFO_SIZE_VERSION_400); // must be
		mii.cbSize = MENUITEMINFO_SIZE_VERSION_400;
	}
#endif // (WINVER >= 0x0500)

	return mii;
}


#if !defined(_WIN32_WCE)

	inline WINDOWPLACEMENT& pstade_tomato_version_initialize(WINDOWPLACEMENT& wndpl, pstade::overload)
	{
		wndpl.length = sizeof(WINDOWPLACEMENT);
		return wndpl;
	}

#endif // !defined(_WIN32_WCE)
