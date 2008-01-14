#ifndef PSTADE_GRAVY_DETAIL_PATH_FIND_FILE_NAME_HPP
#define PSTADE_GRAVY_DETAIL_PATH_FIND_FILE_NAME_HPP


// PStade.Gravy
//
// Copyright Shunsuke Sogame 2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/assert.hpp>
#include "../c_str.hpp"
#include "../dir_sep.hpp"
#include "../sdk/config.hpp" // SDK_NO_SHLWAPI
#include "../sdk/shlwapi.hpp" // PathFindFileName
#include "../sdk/tchar.hpp"
#include "../sdk/windows.hpp"


namespace pstade { namespace gravy { namespace detail {


#if !defined(PSTADE_GRAVY_NO_SHLWAPI)


    template<class CStringizable> inline
    TCHAR const *path_find_file_name(CStringizable const& path)
    {
        return ::PathFindFileName(path|c_str);
    }


#else


    template<class CStringizable> inline
    TCHAR const *path_find_file_name(CStringizable const& path)
    {
        TCHAR const *pszPath = path|c_str;
        TCHAR const *pszFileName = pszPath; // beginning of the path if failed

        for (TCHAR const *psz = pszPath; *psz != _T('\0'); psz = ::CharNext(psz)) {
            if (*psz == dir_tsep::value) {
                psz = ::CharNext(psz);
                if (*psz != _T('\0')) {
                    BOOST_ASSERT(*psz != dir_tsep::value);
                    pszFileName = psz;
                }
            }
        }

        return pszFileName;
    }


#endif // !defined(PSTADE_GRAVY_NO_SHLWAPI)


    inline
    TCHAR *path_find_file_name(TCHAR *pszPath)
    {
        TCHAR const *psz = pszPath;
        return const_cast<TCHAR *>(detail::path_find_file_name(psz));
    }


} } } // namespace pstade::gravy::detail


#endif
