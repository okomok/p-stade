#ifndef PSTADE_TOMATO_FILESYSTEM_PATH_FIND_EXTENSION_HPP
#define PSTADE_TOMATO_FILESYSTEM_PATH_FIND_EXTENSION_HPP


// PStade.Tomato
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// See:
//
// ATL3::AtlModuleLoadTypeLib


// Note:
//
// _tsplitpath requires CRT


#include <boost/assert.hpp>
#include <boost/microsoft/sdk/config.hpp> // SDK_NO_SHLWAPI
#include <boost/microsoft/sdk/shlwapi.hpp> // PathFindExtension
#include <boost/microsoft/sdk/tchar.hpp>
#include <boost/microsoft/sdk/windows.hpp>
#include "../diet/valid.hpp"


namespace pstade { namespace tomato {


#if !defined(BOOST_MICROSOFT_SDK_NO_SHLWAPI)


    inline
    const TCHAR *path_find_extension(const TCHAR *pszPath)
    {
        BOOST_ASSERT(diet::valid(pszPath));

        return ::PathFindExtension(pszPath);
    }


    inline
    TCHAR *path_find_extension(TCHAR *pszPath)
    {
        BOOST_ASSERT(diet::valid(pszPath));

        return ::PathFindExtension(pszPath);
    }


#else


    inline
    const TCHAR *path_find_extension(const TCHAR *pszPath)
    {
        BOOST_ASSERT(diet::valid(pszPath));

        const TCHAR *psz = pszPath;
        for ( ; *psz != _T('\0'); psz = ::CharNext(psz)) {
            if (*psz == _T('.'))
                break;
        }

        return psz; // end of the path if failed
    }


    inline
    TCHAR *path_find_extension(TCHAR *pszPath)
    {
        BOOST_ASSERT(diet::valid(pszPath));

        const TCHAR *psz = pszPath;
        return const_cast<TCHAR *>(tomato::path_find_extension(psz));
    }


#endif // !defined(BOOST_MICROSOFT_SDK_NO_SHLWAPI)


} } // namespace pstade::tomato


#endif
