#ifndef PSTADE_TOMATO_GDI_FONT_HEIGHT_FROM_DECIPOINT_HPP
#define PSTADE_TOMATO_GDI_FONT_HEIGHT_FROM_DECIPOINT_HPP


// PStade.Tomato
//
// Copyright 2006 MB.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// Port of:
//
// WTL::CLogFont::SetHeightFromDeciPoint


#include <boost/assert.hpp>
#include <boost/microsoft/sdk/windows.hpp>
#include "../diet/valid.hpp"
#include "./screen_dc_if_null.hpp"


namespace pstade { namespace tomato {


namespace font_height_from_decipoint_detail {


	inline
	LONG aux(LONG lDeciPtHeight, HDC hDC)
	{

		BOOST_ASSERT(diet::valid(hDC));

	#if !defined(_WIN32_WCE)
		POINT pt = { 0, 0 };
		pt.y = ::MulDiv(::GetDeviceCaps(hDC, LOGPIXELSY), lDeciPtHeight, 720);
		::DPtoLP(hDC, &pt, 1);
		POINT ptOrg = { 0, 0 };
		::DPtoLP(hDC, &ptOrg, 1);
		return -abs(pt.y - ptOrg.y);
	#else
		return -abs(::MulDiv(::GetDeviceCaps(hDC, LOGPIXELSY), lDeciPtHeight, 720));
	#endif // !defined(_WIN32_WCE)
	}


} // namespace font_height_from_decipoint_detail


inline
LONG font_height_from_decipoint(LONG lDeciPtHeight, HDC hDC)
{
	screen_dc_if_null dc(hDC);
	return font_height_from_decipoint_detail::aux(lDeciPtHeight, dc.get_handle());
}


} } // namespace pstade::tomato


#endif
