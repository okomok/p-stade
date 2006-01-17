#pragma once

#include <boost/array.hpp>
#include <boost/range/begin.hpp>
#include "../diagnostic/is_valid.hpp"
#include "./fill_class_name.hpp"

namespace pstade { namespace tomato {


inline bool is_object_of(HWND hWnd, LPCTSTR pszClassName)
{
	ATLASSERT(tomato::is_valid(hWnd));
	ATLASSERT(tomato::is_valid(pszClassName));

	boost::array<TCHAR, 256> buf;
	tomato::fill_class_name(hWnd, buf);

	// Note: You cannot use boost::equals that doesn't support WinCE.
	return lstrcmp(pszClassName, boost::const_begin(buf)) == 0;
}


} } // namespace pstade::tomato
