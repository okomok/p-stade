#pragma once

#include <boost/scoped_array.hpp>
#include <pstade/overload.hpp>

namespace pstade { namespace tomato {


///////////////////////////////////////////////////////////////////////////////
// profile_set_binary (optional)
//
template< class Profile > inline
void profile_set_binary(Profile& pr, LPCTSTR pszValueName, const void *pValue, ULONG nBytes)
{
	pstade_tomato_profile_set_binary(pr, pszValueName, pValue, nBytes, overload());
}


} } // namespace pstade::tomato


///////////////////////////////////////////////////////////////////////////////
// default
//
template< class Profile >
void pstade_tomato_profile_set_binary(Profile& pr, LPCTSTR pszValueName, const void *pValue, ULONG nBytes, ...)
{
	// See: MFC7::CWinApp::WriteProfileBinary

	ATLASSERT(pValue != NULL);

	boost::scoped_array<TCHAR> sz(new TCHAR[nBytes*2+1]);
	BYTE const *pVal = pValue;

	// convert to string and write out
	for (UINT i = 0; i < nBytes; ++i) {
		sz[i*2] = (TCHAR)((pVal[i] & 0x0F) + 'A'); // low nibble
		sz[i*2+1] = (TCHAR)(((pVal[i] >> 4) & 0x0F) + 'A'); // high nibble
	}
	sz[i*2] = 0; // makes sz "sz"

	tomato::profile_set_string(pr, pszValueName, sz);
}
