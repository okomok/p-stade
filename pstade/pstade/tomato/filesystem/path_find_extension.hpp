#pragma once

// Note: _tsplitpath requires CRT

//#if (_ATL_VER >= 0x0700)
//#include <atlpath.h>
//#endif // !(_ATL_VER >= 0x0700)

namespace pstade { namespace tomato {


#if (_WIN32_IE >= 0x0400) && !defined(_WIN32_WCE)

inline LPTSTR path_find_extension(LPCTSTR pszPath)
{
	return ::PathFindExtension(pszPath);
}

#else

inline LPTSTR path_find_extension(LPCTSTR pszPath)
{
	// See: ATL3::AtlModuleLoadTypeLib

	LPCTSTR psz = pszPath;
	for ( ; *psz != _T('\0'); psz = ::CharNext(psz))
	{
		if (*psz == _T('.'))
			break;
	}

	return const_cast<LPTSTR>(psz); // end of the path if failed
}

#endif // (_WIN32_IE >= 0x0400) && !defined(_WIN32_WCE)


} } // namespace pstade::tomato
