#pragma once

#include "./dir_separator.hpp"

namespace pstade { namespace tomato {


#if (_WIN32_IE >= 0x0400) && !defined(_WIN32_WCE)

	inline LPTSTR path_find_file_name(LPCTSTR pszPath)
	{
		return ::PathFindFileName(pszPath);
	}

#else

	inline LPTSTR path_find_file_name(LPCTSTR pszPath)
	{
		LPCTSTR pszFileName = pszPath; // beginning of the path if failed

		for (LPCTSTR psz = pszPath; *psz != null_tchar::value; psz = ::CharNext(psz)) {
			if (*psz == dir_separator::value) {
				psz = ::CharNext(psz);
				if (*psz != _T('\0')) {
					ATLASSERT(*psz != dir_separator::value);
					pszFileName = psz;
				}
			}
		}

		return const_cast<LPTSTR>(pszFileName);
	}

#endif // (_WIN32_IE >= 0x0400) && !defined(_WIN32_WCE)


} } // namespace pstade::tomato
