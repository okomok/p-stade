#ifndef PSTADE_PIZZA_GET_WRITE_FONT_HPP
#define PSTADE_PIZZA_GET_WRITE_FONT_HPP


// PStade.Pizza
//
// Copyright 2006 MB.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/assert.hpp>
#include <boost/microsoft/atl/win.hpp> // CWindow
#include <boost/microsoft/sdk/windows.hpp>
#include <boost/microsoft/wtl/gdi.hpp> // CLogFont
#include <pstade/require.hpp>
#include <pstade/tomato/diet/valid.hpp>
#include "./logfont.hpp"


namespace pstade { namespace pizza {


template< class Profile >
void write_font(Profile& pr, HWND hWnd)
{
	BOOST_ASSERT(diet::valid(hWnd));

	HFONT hFont = ATL::CWindow(hWnd).GetFont();
	if (hFont == NULL)
		return;

	pizza::write_logfont(pr, WTL::CLogFont(hFont));
}


// Deprecated?
//
template< class Profile >
bool get_font(Profile& pr, HWND hWnd)
{
	BOOST_ASSERT(diet::valid(hWnd));

	LOGFONT lf;
	if (!pizza::get_logfont(pr, lf))
		return false;

	HFONT hFont = ::CreateFontIndirect(&lf);
	PSTADE_REQUIRE(hFont != NULL);

	ATL::CWindow(hWnd).SetFont(hFont);

	return true;
}


} } // namespace pstade::pizza


#endif
