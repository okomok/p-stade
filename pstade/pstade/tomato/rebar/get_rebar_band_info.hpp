#pragma once

#include <pstade/integral_cast.hpp>
#include "../cast/boolean_cast.hpp"
#include "../diagnostic/is_valid.hpp"
#include "../diagnostic/verify.hpp"

namespace pstade { namespace tomato {


// Any window can pretend to be a toolbar:^)

// See: WTL7.5::CFrameWindowImpl<>::AddSimpleReBarBandCtrl
namespace get_rebar_band_info_detail {

	inline int get_button_count(HWND hWnd)
	{
		return pstade::integral_cast<int>(::SendMessage(hWnd, TB_BUTTONCOUNT, 0, 0L));
	}

	inline bool get_first_item_rect(HWND hWnd, RECT& rc)
	{
		int nBtnCount = get_button_count(hWnd);
		if (nBtnCount > 0)
		{
			tomato::api_verify( tomato::boolean_cast<BOOL>(::SendMessage(hWnd, TB_GETITEMRECT, 0, (LPARAM)&rc)) );
			return true;
		}

		return false;
	}

	inline bool get_last_item_rect(HWND hWnd, RECT& rc)
	{
		int nBtnCount = get_button_count(hWnd);
		if (nBtnCount > 0)
		{
			tomato::api_verify( tomato::boolean_cast<BOOL>(::SendMessage(hWnd, TB_GETITEMRECT, nBtnCount-1, (LPARAM)&rc)) );
			return true;
		}

		return false;
	}

} // namespace get_rebar_band_info_detail


inline UINT get_rebar_band_info_cxMinChild(HWND hWnd, bool hasTitle)
{
	ATLASSERT(tomato::is_valid(hWnd));
	
	if (hasTitle)
		return 0;

	RECT rc;
	if (get_rebar_band_info_detail::get_first_item_rect(hWnd, rc))
		return rc.right;

	return 0;
}


inline UINT get_rebar_band_info_cyMinChild(HWND hWnd)
{
	ATLASSERT(tomato::is_valid(hWnd));
	
	RECT rc;
	if (get_rebar_band_info_detail::get_first_item_rect(hWnd, rc))
		return rc.bottom - rc.top;

	return 16;
}


inline UINT get_rebar_band_info_cxIdeal(HWND hWnd)
{
	ATLASSERT(tomato::is_valid(hWnd));
	
	RECT rc;
	if (get_rebar_band_info_detail::get_last_item_rect(hWnd, rc))
		return rc.right;

	return 0;
}


} } // namespace pstade::tomato
