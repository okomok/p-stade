#pragma once

#include <atlctrls.h>
#include "../diagnostic/is_valid.hpp"
#include "../diagnostic/verify.hpp"
#include "../structure/version_initialize.hpp"

namespace pstade { namespace tomato {


inline HWND get_rebar_band_hwnd(HWND hWndReBar, UINT uBandID)
{
	ATLASSERT(tomato::is_valid(hWndReBar));
	
	WTL::CReBarCtrl rebar(hWndReBar);
	int index = rebar.IdToIndex(uBandID);
	// Note: RB_IDTOINDEX doesn't use GetLastError().
	ATLASSERT(index != -1 && "tomato::get_rebar_band_hwnd - band id is invalid.");

	REBARBANDINFO info;
	tomato::version_initialize(info);
	info.fMask = RBBIM_CHILD;

	tomato::api_verify(rebar.GetBandInfo(index, &info));
	return info.hwndChild;
}


} } // namespace pstade::tomato
