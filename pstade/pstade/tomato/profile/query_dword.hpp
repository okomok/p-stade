#pragma once

#include <boost/array.hpp>
#include <boost/range/begin.hpp>
#include <pstade/overload.hpp>
#include "../algorithm/tstoi.hpp"
#include "../diagnostic/is_valid.hpp"
#include "./query_string.hpp"

namespace pstade { namespace tomato {


///////////////////////////////////////////////////////////////////////////////
// profile_query_dword_value (optional)
//
template< class Profile >
inline bool profile_query_dword(Profile& pr, LPCTSTR pszValueName, DWORD& dwValue)
{
	return pstade_tomato_profile_query_dword(pr, pszValueName, dwValue, overload());
}


} } // namespace pstade::tomato


///////////////////////////////////////////////////////////////////////////////
// default
//
template< class Profile >
bool pstade_tomato_profile_query_dword(Profile& pr, LPCTSTR pszValueName, DWORD& dwValue, ...)
{
	boost::array<TCHAR, 16> szValue;
	if (!tomato::profile_query_string(pr, pszValueName, szValue))
		return false;

	ATLASSERT(tomato::is_valid(boost::const_begin(szValue)));

	dwValue = tomato::tstoi(boost::const_begin(szValue));
	return true;
}
