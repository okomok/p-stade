#ifndef PSTADE_TOMATO_GDI_DECIPOINT_FONT_FROM_HEIGHT_HPP
#define PSTADE_TOMATO_GDI_DECIPOINT_FONT_FROM_HEIGHT_HPP


// PStade.Tomato
//
// Copyright 2006 MB.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// Port of:
//
// WTL::CLogFont::GetDeciPointHeight and WTL::CFont::CreatePointFontIndirect


#include <boost/assert.hpp>
#include <boost/microsoft/sdk/windows.hpp>
#include "../diet/valid.hpp"
#include "./screen_dc_if_null.hpp"


namespace pstade { namespace tomato {


namespace decipoint_font_height_detail {


	inline
	LONG aux(LONG lfHeight, HDC hDC)
	{
		BOOST_ASSERT(diet::valid(hDC));

	#if !defined(_WIN32_WCE)
		POINT ptOrg = { 0, 0 };
		::DPtoLP(hDC, &ptOrg, 1);
		POINT pt = { 0, 0 };
		pt.y = abs(lfHeight) + ptOrg.y;
		::LPtoDP(hDC,&pt,1);
		return ::MulDiv(pt.y, 720, ::GetDeviceCaps(hDC, LOGPIXELSY));
	#else
		return ::MulDiv(abs(lfHeight), 720, ::GetDeviceCaps(hDC, LOGPIXELSY));
	#endif
	}


} // namespace decipoint_font_height


inline
LONG decipoint_font_height(LONG lfHeight, HDC hDC)
{
	screen_dc_if_null dc(hDC);
	return decipoint_font_height_detail::aux(lfHeight, dc.get_handle());
}


} } // namespace pstade::tomato


#endif
