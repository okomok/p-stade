#ifndef PSTADE_TOMATO_DIET_CUSTOMIZATION_HPP
#define PSTADE_TOMATO_DIET_CUSTOMIZATION_HPP


// PStade.Tomato
//
// Copyright 2006 MB.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/assert.hpp>
#include <boost/format.hpp>
#include <boost/microsoft/atl/config.hpp> // ATL_VER
#include <boost/microsoft/atl/core.hpp> // ::AtlIsValidString
#include <boost/microsoft/sdk/tchar.hpp>
#include <boost/microsoft/sdk/windows.hpp>
#include <boost/microsoft/wtl/app.hpp> // ::IsMenu for eVC
#include <boost/mpl/integral_c.hpp>
#include <cstddef> // ptrdiff_t
#include <pstade/nullptr.hpp>
#include <pstade/overload.hpp>
#include <pstade/unused.hpp>
#include "../boolean_cast.hpp"


// HDC
//
inline
bool pstade_diet_is_valid(HDC hDC, pstade::overload)
{
	return (hDC != NULL);
}

template< class OStream > inline
void pstade_diet_dump(HDC hDC, OStream& os, pstade::overload)
{
	os << boost::format("<HDC><handle>%x</handle></HDC>") % hDC;
}


// HMENU
//
inline 
bool pstade_diet_is_valid(HMENU hMenu, pstade::overload)
{
	return pstade::tomato::boolean(::IsMenu(hMenu));
}


template< class OStream > inline
void pstade_diet_dump(HMENU hMenu, OStream& os, pstade::overload)
{
	os << boost::format("<HMENU><handle>%x</handle></HMENU>") % hMenu;
}


// HWND
//
inline 
bool pstade_diet_is_valid(HWND hWnd, pstade::overload)
{
	return pstade::tomato::boolean(::IsWindow(hWnd));
}

template< class OStream > inline
void pstade_diet_dump(HWND hWnd, OStream& os, pstade::overload)
{
	os << boost::format("<HWND><handle>%x</handle></HWND>") % hWnd;
}


// null-terminated string
//   seems not to work under WinXP.
//
inline
bool pstade_diet_is_valid(const TCHAR *psz, pstade::overload)
{
	using namespace pstade;

#if !(BOOST_MICROSOFT_ATL_VER < 0x0700)

	return tomato::boolean(ATL::AtlIsValidString(psz));

#else

	// See: ATL7::AtlIsValidString

	#if defined(NDEBUG)

		return (psz != PSTADE_NULLPTR);

	#else

		if (psz == PSTADE_NULLPTR)
			return false;

		typedef boost::mpl::integral_c<std::ptrdiff_t, 1398269> faraway;

		__try {
			const TCHAR *pch = psz;
			const TCHAR *pchEnd = psz + faraway::value - 1;
			TCHAR ch = *(volatile TCHAR *)pch;
			while ((ch != _T('\0')) && (pch != pchEnd)) {
				++pch;
				ch = *(volatile TCHAR *)pch;

				if (pch == pchEnd) {
					BOOST_ASSERT(false &&
						"null-terminated string candidate is too long to diagnose.");
				}
			}
		}
		__except (EXCEPTION_EXECUTE_HANDLER) {
			return false;
		}

		return true;

	#endif

#endif // !(BOOST_MICROSOFT_ATL_VER < 0x0700)
}

template< class OStream > inline
void pstade_diet_dump(const TCHAR *psz, OStream& os, pstade::overload)
{
	os << boost::format("<cstring><pointer>%x</pointer></cstring>") % static_cast<const void *>(psz);

	pstade::unused(psz);
}


// HINSTANCE
//
inline 
bool pstade_diet_is_valid(HINSTANCE hInst, pstade::overload)
{
	return hInst != NULL;
}

template< class OStream > inline
void pstade_diet_dump(HINSTANCE hInst, OStream& os, pstade::overload)
{
	os << boost::format("<HINSTANCE><handle>%x</handle></HINSTANCE>") % hInst;
}


#endif
