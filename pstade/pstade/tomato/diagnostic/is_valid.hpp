#pragma once

#include <cstddef> // for ptrdiff_t
#include <boost/mpl/integral_c.hpp>
#include <pstade/null_ptr.hpp>
#include <pstade/overload.hpp>
#include "../cast/boolean_cast.hpp"

namespace pstade { namespace tomato {


///////////////////////////////////////////////////////////////////////////////
// is_valid
//
template< class Diagnostic > inline
bool is_valid(const Diagnostic& x)
{
	return pstade_tomato_is_valid(x, overload());
}


} } // namespace pstade::tomato


///////////////////////////////////////////////////////////////////////////////
// default
//
template< class Diagnostic > inline
bool pstade_tomato_is_valid(const Diagnostic& x, ...)
{
	return x.pstade_tomato_is_valid();
}


///////////////////////////////////////////////////////////////////////////////
// c-string
//
inline bool pstade_tomato_is_valid(LPCTSTR psz, pstade::overload)
{
#if (_ATL_VER >= 0x0700)

	return pstade::tomato::boolean_cast<bool>(ATL::AtlIsValidString(psz));

#else

	// See: ATL7::AtlIsValidString

	if (psz == pstade::null_ptr)
		return false;

	typedef boost::mpl::integral_c<std::ptrdiff_t, 1398269> faraway;

	__try {
		LPCTSTR pch = psz;
		LPCTSTR pchEnd = psz + faraway::value - 1;
		TCHAR ch = *(volatile TCHAR*)pch;
		while ((ch != _T('\0')) && (pch != pchEnd)) {
			++pch;
			ch = *(volatile TCHAR*)pch;

			if (pch == pchEnd) {
				ATLASSERT(false && "pstade::tomato::is_valid(LPCTSTR): c-string candidate is too long to diagnose.");
			}
		}
	}
	__except (EXCEPTION_EXECUTE_HANDLER) {
		return false;
	}

	return true;

#endif // (_ATL_VER >= 0x0700)
}

inline bool pstade_tomato_is_valid(LPTSTR psz, pstade::overload)
{
	return pstade::tomato::is_valid(static_cast<LPCTSTR>(psz));
}


///////////////////////////////////////////////////////////////////////////////
// HWND
//
inline bool pstade_tomato_is_valid(HWND hWnd, pstade::overload)
{
	if (hWnd == NULL)
		return false;

	return pstade::tomato::boolean_cast<bool>(::IsWindow(hWnd));
}


///////////////////////////////////////////////////////////////////////////////
// HMENU
//
inline bool pstade_tomato_is_valid(HMENU hMenu, pstade::overload)
{
	if (hMenu == NULL)
		return false;

#if !defined(_WIN32_WCE)
	return pstade::tomato::boolean_cast<bool>(::IsMenu(hMenu));
#else
	return true;
#endif
}


///////////////////////////////////////////////////////////////////////////////
// HDC
//
inline bool pstade_tomato_is_valid(HDC hDC, pstade::overload)
{
	return (hDC != NULL);
}
