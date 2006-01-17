#pragma once

#include <boost/array.hpp>
#include <boost/range/begin.hpp>
#include <pstade/overload.hpp>

namespace pstade { namespace tomato {


///////////////////////////////////////////////////////////////////////////////
// profile_set_dword (optional)
//
template< class Profile > inline
void profile_set_dword(Profile& pr, LPCTSTR pszValueName, DWORD dwValue)
{
	pstade_tomato_profile_set_dword(pr, pszValueName, dwValue, overload());
}


} } // namespace pstade::tomato


///////////////////////////////////////////////////////////////////////////////
// default
//
template< class Profile >
void pstade_tomato_profile_set_dword(Profile& pr, LPCTSTR pszValueName, DWORD dwValue, ...)
{
	boost::array<TCHAR, 16> sz;
	wsprintf(boost::begin(sz), _T("%d"), dwValue);

	tomato::profile_set_string(pr, pszValueName, boost::const_begin(sz));
}
