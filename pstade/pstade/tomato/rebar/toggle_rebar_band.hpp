#pragma once

#include "../diagnostic/is_valid.hpp"
#include "./is_rebar_band_visible.hpp"
#include "./show_rebar_band.hpp"

namespace pstade { namespace tomato {


inline BOOL toggle_rebar_band(HWND hWndReBar, UINT uBandID)
{
	ATLASSERT(tomato::is_valid(hWndReBar));

	BOOL bNew = !tomato::is_rebar_band_visible(hWndReBar, uBandID);
	tomato::show_rebar_band(hWndReBar, uBandID, bNew);
	return bNew;
}


} } // namespace pstade::tomato
