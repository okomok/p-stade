#pragma once

#include <atlctrls.h>
#include <pstade/candy/set.hpp>
#include "../diagnostic/is_valid.hpp"
#include "../diagnostic/verify.hpp"
#include "../rebar/get_rebar_band_info.hpp"
#include "../structure/version_initialize.hpp"

namespace pstade { namespace tomato {


// lpText can be NULL.
// cx can be 0.
inline void add_rebar_band(HWND hWndReBar, HWND hWndBand, UINT fStyle, LPCTSTR lpText, UINT cx)
{
	ATLASSERT(tomato::is_valid(hWndReBar));
	ATLASSERT(tomato::is_valid(hWndBand));
	ATLASSERT(::GetDlgCtrlID(hWndBand) != 0 && "pstade::tomato::add_rebar_band - child window id is invalid.");
	
	REBARBANDINFO info;
	tomato::version_initialize(info);

#if (_WIN32_IE >= 0x0400)
	info.fMask = RBBIM_CHILD | RBBIM_CHILDSIZE | RBBIM_STYLE | RBBIM_ID | RBBIM_SIZE | RBBIM_IDEALSIZE;
#else
	info.fMask = RBBIM_CHILD | RBBIM_CHILDSIZE | RBBIM_STYLE | RBBIM_ID | RBBIM_SIZE;
#endif
	
	if (lpText != NULL)
		candy::set(info.fMask, RBBIM_TEXT);
	
	info.fStyle = fStyle;
	info.lpText = const_cast<LPTSTR>(lpText);
	info.hwndChild = hWndBand;
	info.wID = ::GetDlgCtrlID(hWndBand); // how's that

	info.cxMinChild = tomato::get_rebar_band_info_cxMinChild(hWndBand, lpText != NULL);
	info.cyMinChild = tomato::get_rebar_band_info_cyMinChild(hWndBand);
	
	// cx is the "current" width.
	if (cx == 0)
		info.cx = tomato::get_rebar_band_info_cxIdeal(hWndBand);
	else
		info.cx = cx;

#if (_WIN32_IE >= 0x0400)
	// Note: cxIdeal is used for CHEVRON. If MDI, cxIdeal is changed dynamically.
	info.cxIdeal = tomato::get_rebar_band_info_cxIdeal(hWndBand); // info.cx is not good.
#endif

	WTL::CReBarCtrl rebar(hWndReBar);
	tomato::api_verify(rebar.InsertBand(-1, &info));

/*
#if (_WIN32_IE >= 0x0501)
		DWORD dwExStyle = (DWORD)::SendMessage(hWndBand, TB_GETEXTENDEDSTYLE, 0, 0L);
		::SendMessage(hWndBand, TB_SETEXTENDEDSTYLE, 0, dwExStyle | TBSTYLE_EX_HIDECLIPPEDBUTTONS);
#endif // (_WIN32_IE >= 0x0501)
*/

}


} } // namespace pstade::tomato
