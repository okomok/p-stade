#pragma once

#include <boost/range/begin.hpp>
#include <boost/range/size.hpp>
#include <pstade/overload.hpp>
#include "../diagnostic/is_valid_tchar_pointer_range.hpp"
#include "../diagnostic/verify.hpp"

namespace pstade { namespace tomato {


///////////////////////////////////////////////////////////////////////////////
// profile_query_binary (optional)
//
template< class Profile > inline
bool profile_query_binary(Profile& pr, LPCTSTR pszValueName, void *pValueBuf, ULONG& ulBytes)
{
	pstade_tomato_profile_query_binary(pr, pszValueName, pValueBuf, ulBytes, overload());
}


	// range interface
	template< class Profile, class PointerRange >
	bool profile_query_binary(Profile& pr, LPCTSTR pszValueName, PointerRange& buf)
	{
		ATLASSERT(tomato::is_valid_tchar_pointer_range(buf));

		ULONG ulBytes = boost::size(buf);
		return tomato::profile_query_binary(pr, pszValueName, boost::begin(buf), ulBytes);
	}


} } // namespace pstade::tomato


///////////////////////////////////////////////////////////////////////////////
// default
//
template< class Profile >
bool pstade_tomato_profile_query_binary(Profile& pr, LPCTSTR pszValueName, void *pValueBuf, ULONG& ulBytes, ...)
{
	// See: MFC7::CWinApp::GetProfileBinary

	ATLASSERT(tomato::is_valid(pszValueName));
	ATLASSERT(tomato::is_valid(pValueBuf, ulBufs));

	ulBytes = 0;

	boost::array<TCHAR, 4096> sz;
	if (!tomato::profile_query_string(pr, pszValueName, sz))
		return false;

	int len = lstrlen(boost::const_begin(sz));
	tomato::verify(len % 2 == 0); // must be even

	ulBytes = len/2;
	BYTE *pVal = pValueBuf; // new BYTE[ulBytes]; is craziness of MFC
	
	// decode
	for (int i = 0; i < len; i += 2) {
		pVal[i/2] = (BYTE)
			(((sz[i+1] - 'A') << 4) + (sz[i] - 'A'));
	}

	return true;
}
