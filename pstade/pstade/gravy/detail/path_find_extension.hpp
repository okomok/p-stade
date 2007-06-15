#ifndef PSTADE_GRAVY_DETAIL_PATH_FIND_EXTENSION_HPP
#define PSTADE_GRAVY_DETAIL_PATH_FIND_EXTENSION_HPP


// PStade.Gravy
//
// Copyright Shunsuke Sogame 2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// See:
//
// ATL3::AtlModuleLoadTypeLib


// Note:
//
// _tsplitpath requires CRT


#include "../c_str.hpp"
#include "../sdk/config.hpp" // SDK_NO_SHLWAPI
#include "../sdk/shlwapi.hpp" // PathFindExtension
#include "../sdk/tchar.hpp"
#include "../sdk/windows.hpp"


namespace pstade { namespace gravy { namespace detail {


#if !defined(PSTADE_GRAVY_NO_SHLWAPI)


    template<class CStringizable> inline
    TCHAR const *path_find_extension(CStringizable const& path)
    {
        return ::PathFindExtension(path|c_str);
    }


#else


    template<class CStringizable> inline
    TCHAR const *path_find_extension(CStringizable const& path)
    {
        TCHAR const *psz = path|c_str;
        for ( ; *psz != _T('\0'); psz = ::CharNext(psz)) {
            if (*psz == _T('.'))
                break;
        }

        return psz; // end of the path if failed
    }


#endif // !defined(PSTADE_GRAVY_NO_SHLWAPI)


    inline
    TCHAR *path_find_extension(TCHAR *pszPath)
    {
        TCHAR const *psz = pszPath;
        return const_cast<TCHAR *>(detail::path_find_extension(psz));
    }


} } } // namespace pstade::gravy::detail


#endif
