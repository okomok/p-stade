#ifndef PSTADE_GRAVY_DETAIL_IS_OLD_WINDOWS_HPP
#define PSTADE_GRAVY_DETAIL_IS_OLD_WINDOWS_HPP


// PStade.Gravy
//
// Copyright Shunsuke Sogame 2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include "../sdk/windows.hpp"


namespace pstade { namespace gravy { namespace detail {


    inline
    bool is_old_windows()
    {
        OSVERSIONINFO ovi = { 0 };
        ovi.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);
        BOOL bRet = ::GetVersionEx(&ovi);
        return (!bRet || !((ovi.dwMajorVersion >= 5) || (ovi.dwMajorVersion == 4 && ovi.dwMinorVersion >= 90)));
    }


} } } // namespace pstade::gravy::detail


#endif
