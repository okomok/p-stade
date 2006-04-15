#ifndef PSTADE_TOMATO_FILESYSTEM_PATH_FIND_FILE_NAME_HPP
#define PSTADE_TOMATO_FILESYSTEM_PATH_FIND_FILE_NAME_HPP


// PStade.Tomato
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/assert.hpp>
#include <boost/microsoft/sdk/config.hpp> // SDK_NO_SHLWAPI
#include <boost/microsoft/sdk/shlwapi.hpp> // PathFindFileName
#include <boost/microsoft/sdk/tchar.hpp>
#include <boost/microsoft/sdk/windows.hpp>
#include "./dir_sep_value.hpp"
#include "../diet/valid.hpp"


namespace pstade { namespace tomato {


#if !defined(BOOST_MICROSOFT_SDK_NO_SHLWAPI)


	inline
	const TCHAR *path_find_file_name(const TCHAR *pszPath)
	{
		BOOST_ASSERT(diet::valid(pszPath));

		return ::PathFindFileName(pszPath);
	}


	inline
	TCHAR *path_find_file_name(TCHAR *pszPath)
	{
		BOOST_ASSERT(diet::valid(pszPath));

		return ::PathFindFileName(pszPath);
	}


#else


	inline
	const TCHAR *path_find_file_name(const TCHAR *pszPath)
	{
		BOOST_ASSERT(diet::valid(pszPath));

		const TCHAR *pszFileName = pszPath; // beginning of the path if failed

		for (const TCHAR *psz = pszPath; *psz != _T('\0'); psz = ::CharNext(psz)) {
			if (*psz == tdir_sep::value) {
				psz = ::CharNext(psz);
				if (*psz != _T('\0')) {
					BOOST_ASSERT(*psz != tdir_sep::value);
					pszFileName = psz;
				}
			}
		}

		return pszFileName;
	}


	inline
	TCHAR *path_find_file_name(TCHAR *pszPath)
	{
		BOOST_ASSERT(diet::valid(pszPath));

		const TCHAR *psz = pszPath;
		return const_cast<TCHAR *>(tomato::path_find_file_name(psz));
	}


#endif // !defined(BOOST_MICROSOFT_SDK_NO_SHLWAPI)


} } // namespace pstade::tomato


#endif
