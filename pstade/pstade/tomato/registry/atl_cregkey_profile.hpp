#pragma once

#include <pstade/overload.hpp>
#include "../diagnostic/verify.hpp"
#include "../filesystem/get_module_name.hpp"


///////////////////////////////////////////////////////////////////////////////
// profile_initialize
//
template< class StringT >
void pstade_tomato_profile_initialize(ATL::CRegKey& key, const StringT& name, pstade::overload)
{
	StringT module_name;
	pstade::tomato::get_module_name(module_name);
	StringT path = _T("Software\\") + module_name + _T('\\') + name;
	
	pstade::tomato::verify(key.Create(HKEY_CURRENT_USER, path) == ERROR_SUCCESS, E_ACCESSDENIED);
}


///////////////////////////////////////////////////////////////////////////////
// profile_set_dword
//
inline void pstade_tomato_profile_set_dword(ATL::CRegKey& key, LPCTSTR pszValueName, DWORD dwValue, pstade::overload)
{
#if (_ATL_VER >= 0x0700)
	pstade::tomato::verify(key.SetDWORDValue(pszValueName, dwValue) == ERROR_SUCCESS, E_ACCESSDENIED);
#else
	pstade::tomato::verify(key.SetValue(dwValue, pszValueName) == ERROR_SUCCESS, E_ACCESSDENIED);
#endif // (_ATL_VER >= 0x0700)
}


///////////////////////////////////////////////////////////////////////////////
// profile_query_dword
//
inline bool pstade_tomato_profile_query_dword(ATL::CRegKey& key, LPCTSTR pszValueName, DWORD& dwValue, pstade::overload)
{
#if (_ATL_VER >= 0x0700)
	return key.QueryDWORDValue(pszValueName, dwValue) == ERROR_SUCCESS;
#else
	return key.QueryValue(dwValue, pszValueName) == ERROR_SUCCESS;
#endif // (_ATL_VER >= 0x0700)
}


///////////////////////////////////////////////////////////////////////////////
// profile_set_string
//
inline void pstade_tomato_profile_set_string(ATL::CRegKey& key, LPCTSTR pszValueName, LPCTSTR pszValue, pstade::overload)
{
#if (_ATL_VER >= 0x0700)
	pstade::tomato::verify(key.SetStringValue(pszValueName, pszValue) == ERROR_SUCCESS, E_ACCESSDENIED);
#else
	pstade::tomato::verify(key.SetValue(pszValue, pszValueName) == ERROR_SUCCESS, E_ACCESSDENIED);
#endif // (_ATL_VER >= 0x0700)
}


///////////////////////////////////////////////////////////////////////////////
// profile_query_string
//
inline bool pstade_tomato_profile_query_string(ATL::CRegKey& key, LPCTSTR pszValueName, TCHAR *pOutBuf, ULONG& ulBufs, pstade::overload)
{
#if (_ATL_VER >= 0x0700)
	return key.QueryStringValue(pszValueName, pOutBuf, &ulBufs) == ERROR_SUCCESS;
#else
	return key.QueryValue(pOutBuf, pszValueName, &ulBufs) == ERROR_SUCCESS;
#endif // (_ATL_VER >= 0x0700)
}


///////////////////////////////////////////////////////////////////////////////
// profile_delete
//
inline void pstade_tomato_profile_delete(ATL::CRegKey& key, LPCTSTR pszValueName, pstade::overload)
{
	pstade::tomato::verify(key.DeleteValue(pszValueName) == ERROR_SUCCESS, E_ACCESSDENIED);
}


#if (_ATL_VER >= 0x0700)

	///////////////////////////////////////////////////////////////////////////////
	// profile_delete
	//
	inline void pstade_tomato_profile_set_binary(ATL::CRegKey& key, LPCTSTR pszValueName, const void *pValue, ULONG nBytes, pstade::overload)
	{
		pstade::tomato::verify(key.SetBinaryValue(pszValueName, pValue, nBytes) == ERROR_SUCCESS, E_ACCESSDENIED);
	}

	inline bool pstade_tomato_profile_query_binary(ATL::CRegKey& key, LPCTSTR pszValueName, void *pValueBuf, ULONG& ulBytes, pstade::overload)
	{
		return key.QueryBinaryValue(pszValueName, pValueBuf, &ulBytes) == ERROR_SUCCESS;
	}

#endif // (_ATL_VER >= 0x0700)
