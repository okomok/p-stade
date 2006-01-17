#pragma once

#include <atlctrls.h>
#include <pstade/candy/test.hpp>
#include "../cast/boolean_cast.hpp"
#include "../diagnostic/is_valid.hpp"
#include "../diagnostic/verify.hpp"
#include "../structure/version_initialize.hpp"

namespace pstade { namespace tomato {


inline BOOL is_rebar_band_visible(HWND hWndReBar, UINT uBandID)
{
	ATLASSERT(tomato::is_valid(hWndReBar));

	WTL::CReBarCtrl rebar(hWndReBar);
	int index = rebar.IdToIndex(uBandID);
	ATLASSERT(index != -1 && "pstade::tomato::is_rebar_band_visible - band id is invalid.");

	REBARBANDINFO info;
	tomato::version_initialize(info);
	info.fMask = RBBIM_STYLE;

	tomato::api_verify(rebar.GetBandInfo(index, &info));
	return !tomato::boolean_cast<BOOL>(candy::test(info.fStyle, RBBS_HIDDEN));
}


} } // namespace pstade::tomato
