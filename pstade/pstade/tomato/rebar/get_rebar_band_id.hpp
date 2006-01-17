#pragma once

#include <atlctrls.h>
#include "../diagnostic/is_valid.hpp"
#include "../diagnostic/verify.hpp"
#include "../structure/version_initialize.hpp"

namespace pstade { namespace tomato {


inline UINT get_rebar_band_id(HWND hWndReBar, int index)
{
	ATLASSERT(tomato::is_valid(hWndReBar));
	ATLASSERT(index >= 0);

	REBARBANDINFO info;
	tomato::version_initialize(info);
	info.fMask = RBBIM_ID;

	WTL::CReBarCtrl rebar(hWndReBar);
	tomato::api_verify(rebar.GetBandInfo(index, &info));
	return info.wID;
}


} } // namespace pstade::tomato
