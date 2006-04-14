#ifndef PSTADE_PIZZA_REG_KEY_HPP
#define PSTADE_PIZZA_REG_KEY_HPP


// PStade.Pizza
//
// Copyright 2006 MB.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <cstddef> // size_t
#include <boost/microsoft/atl/base.hpp> // CRegKey
#include <boost/microsoft/atl/config.hpp> // ATL_VER
#include <boost/microsoft/sdk/tchar.hpp>
#include <boost/microsoft/sdk/windows.hpp>
#include <pstade/integral_cast.hpp>
#include <pstade/oven/sequence_cast.hpp>
#include <pstade/overload.hpp>
#include <pstade/tomato/c_str.hpp>
#include <pstade/tomato/filesystem/module_file_name.hpp>
#include <pstade/tomato/tstring.hpp>
#include <pstade/require.hpp>


inline
void pstade_pizza_initialize(ATL::CRegKey& key, const TCHAR *pszName, pstade::overload)
{
	using namespace pstade;

	tomato::tstring moduleName = oven::sequence(tomato::module_file_name().name());
	tomato::tstring path = _T("Software\\") + moduleName + _T('\\') + pszName;
	
	PSTADE_REQUIRE(key.Create(HKEY_CURRENT_USER, tomato::c_str(path)) == ERROR_SUCCESS);
}


inline
void pstade_pizza_set_string(ATL::CRegKey& key, const TCHAR *pszValueName, const TCHAR *pszValue, pstade::overload)
{
#if !(BOOST_MICROSOFT_ATL_VER < 0x0700)
	PSTADE_REQUIRE(key.SetStringValue(pszValueName, pszValue) == ERROR_SUCCESS);
#else
	PSTADE_REQUIRE(key.SetValue(pszValue, pszValueName) == ERROR_SUCCESS);
#endif
}


inline
bool pstade_pizza_query_string(ATL::CRegKey& key, const TCHAR *pszValueName, TCHAR *pFirst, TCHAR *pLast, pstade::overload)
{
#if !(BOOST_MICROSOFT_ATL_VER < 0x0700)
	ULONG ulBufs = pstade::integral(pLast - pFirst);
	return key.QueryStringValue(pszValueName, pFirst, &ulBufs) == ERROR_SUCCESS;
#else
	DWORD dwCount = pstade::integral(pLast - pFirst);
	return key.QueryValue(pFirst, pszValueName, &dwCount) == ERROR_SUCCESS;
#endif
}


inline
void pstade_pizza_delete(ATL::CRegKey& key, const TCHAR *pszValueName, pstade::overload)
{
	PSTADE_REQUIRE(key.DeleteValue(pszValueName) == ERROR_SUCCESS);
}


#endif
