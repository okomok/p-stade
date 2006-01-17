#pragma once

#include <atlctrls.h>
#include "../diagnostic/is_valid.hpp"
#include "../diagnostic/verify.hpp"

namespace pstade { namespace tomato {


inline void show_rebar_band(HWND hWndReBar, UINT uBandID, BOOL bVisible)
{
	ATLASSERT(tomato::is_valid(hWndReBar));

	WTL::CReBarCtrl rebar(hWndReBar);
	int index = rebar.IdToIndex(uBandID);
	ATLASSERT(index != -1 && "pstade::tomato::show_rebar_band - band id is invalid.");

	tomato::api_verify(rebar.ShowBand(index, bVisible));
}


} } // namespace pstade::tomato
