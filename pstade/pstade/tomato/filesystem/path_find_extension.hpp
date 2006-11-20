#ifndef PSTADE_TOMATO_FILESYSTEM_PATH_FIND_EXTENSION_HPP
#define PSTADE_TOMATO_FILESYSTEM_PATH_FIND_EXTENSION_HPP


// PStade.Tomato
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// See:
//
// ATL3::AtlModuleLoadTypeLib


// Note:
//
// _tsplitpath requires CRT


#include <pstade/apple/sdk/config.hpp> // SDK_NO_SHLWAPI
#include <pstade/apple/sdk/shlwapi.hpp> // PathFindExtension
#include <pstade/apple/sdk/tchar.hpp>
#include <pstade/apple/sdk/windows.hpp>
#include "../c_str.hpp"


namespace pstade { namespace tomato {


#if !defined(PSTADE_APPLE_SDK_NO_SHLWAPI)


    template< class CStringizable > inline
    TCHAR const *path_find_extension(CStringizable const& path)
    {
        return ::PathFindExtension(path|to_c_str);
    }


#else


    template< class CStringizable > inline
    TCHAR const *path_find_extension(CStringizable const& path)
    {
        TCHAR const *psz = path|to_c_str;
        for ( ; *psz != _T('\0'); psz = ::CharNext(psz)) {
            if (*psz == _T('.'))
                break;
        }

        return psz; // end of the path if failed
    }


#endif // !defined(PSTADE_APPLE_SDK_NO_SHLWAPI)


inline
TCHAR *path_find_extension(TCHAR *pszPath)
{
    TCHAR const *psz = pszPath;
    return const_cast<TCHAR *>(tomato::path_find_extension(psz));
}


} } // namespace pstade::tomato


#endif
