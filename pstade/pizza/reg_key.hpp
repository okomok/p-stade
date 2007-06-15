#ifndef PSTADE_PIZZA_REG_KEY_HPP
#define PSTADE_PIZZA_REG_KEY_HPP


// PStade.Pizza
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/detail/overload.hpp>
#include <pstade/gravy/c_str.hpp>
#include <pstade/gravy/module_file_name.hpp>
#include <pstade/gravy/tstring.hpp>
#include <pstade/gravy/sdk/tchar.hpp>
#include <pstade/gravy/sdk/windows.hpp>
#include <pstade/integral_cast.hpp>
#include <pstade/oven/copy_range.hpp>
#include <pstade/tomato/atl/base.hpp> // CRegKey
#include <pstade/tomato/atl/config.hpp> // ATL_VER
#include <pstade/require.hpp>


inline
void pstade_pizza_initialize(ATL::CRegKey& key, const TCHAR *pszName, pstade::detail::overload<>)
{
    using namespace pstade;

    gravy::module_file_name mf;
    gravy::tstring moduleName = mf.name()|oven::copied;
    gravy::tstring path = _T("Software\\") + moduleName + _T('\\') + pszName;
    
    PSTADE_REQUIRE(key.Create(HKEY_CURRENT_USER, gravy::c_str(path)) == ERROR_SUCCESS);
}


inline
void pstade_pizza_set_string(ATL::CRegKey& key, const TCHAR *pszValueName, const TCHAR *pszValue, pstade::detail::overload<>)
{
#if !(PSTADE_TOMATO_ATL_VER < 0x0700)
    PSTADE_REQUIRE(key.SetStringValue(pszValueName, pszValue) == ERROR_SUCCESS);
#else
    PSTADE_REQUIRE(key.SetValue(pszValue, pszValueName) == ERROR_SUCCESS);
#endif
}


inline
bool pstade_pizza_query_string(ATL::CRegKey& key, const TCHAR *pszValueName, TCHAR *pFirst, TCHAR *pLast, pstade::detail::overload<>)
{
#if !(PSTADE_TOMATO_ATL_VER < 0x0700)
    ULONG ulBufs = (pLast - pFirst)|pstade::to_integer;
    return key.QueryStringValue(pszValueName, pFirst, &ulBufs) == ERROR_SUCCESS;
#else
    DWORD dwCount = (pLast - pFirst)|pstade::to_integer;
    return key.QueryValue(pFirst, pszValueName, &dwCount) == ERROR_SUCCESS;
#endif
}


inline
void pstade_pizza_delete(ATL::CRegKey& key, const TCHAR *pszValueName, pstade::detail::overload<>)
{
    PSTADE_REQUIRE(key.DeleteValue(pszValueName) == ERROR_SUCCESS);
}


#endif
