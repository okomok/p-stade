#pragma once

#include "../diagnostic/is_valid.hpp"
#include "./screen_dc_if_null.hpp"

namespace pstade { namespace tomato {


namespace font_height_from_decipoint_detail {

	inline LONG aux(LONG lDeciPtHeight, HDC hDC)
	{
		// See: WTL::CLogFont::SetHeightFromDeciPoint

		ATLASSERT(tomato::is_valid(hDC));

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


inline LONG font_height_from_decipoint(LONG lDeciPtHeight, HDC hDC)
{
	screen_dc_if_null dc(hDC);
	return font_height_from_decipoint_detail::aux(lDeciPtHeight, dc.get_handle());
}


} } // namespace pstade::tomato
