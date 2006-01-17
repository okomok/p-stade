#pragma once

#include "../diagnostic/is_valid.hpp"
#include "./screen_dc_if_null.hpp"

namespace pstade { namespace tomato {


namespace decipoint_font_height_detail {

	inline LONG aux(LONG lfHeight, HDC hDC)
	{
		// See: WTL::CLogFont::GetDeciPointHeight and WTL::CFont::CreatePointFontIndirect, the blob

		ATLASSERT(tomato::is_valid(hDC));

	#if !defined(_WIN32_WCE)
		POINT ptOrg = { 0, 0 };
		::DPtoLP(hDC, &ptOrg, 1);
		POINT pt = { 0, 0 };
		pt.y = abs(lfHeight) + ptOrg.y;
		::LPtoDP(hDC,&pt,1);
		return ::MulDiv(pt.y, 720, ::GetDeviceCaps(hDC, LOGPIXELSY));
	#else
		return ::MulDiv(abs(lfHeight), 720, ::GetDeviceCaps(hDC, LOGPIXELSY));
	#endif // !defined(_WIN32_WCE)
	}

} // namespace decipoint_font_height


inline LONG decipoint_font_height(LONG lfHeight, HDC hDC)
{
	screen_dc_if_null dc(hDC);
	return decipoint_font_height_detail::aux(lfHeight, dc.get_handle());
}


} } // namespace pstade::tomato
