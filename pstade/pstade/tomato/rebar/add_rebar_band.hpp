#ifndef PSTADE_TOMATO_REBAR_ADD_REBAR_BAND_HPP
#define PSTADE_TOMATO_REBAR_ADD_REBAR_BAND_HPP


// PStade.Tomato
//
// Copyright 2006 MB.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <vector>
#include <boost/assert.hpp>
#include <boost/microsoft/sdk/tchar.hpp>
#include <boost/microsoft/sdk/windows.hpp>
#include <boost/microsoft/wtl/ctrls.hpp> // CReBarCtrl
#include <boost/range/begin.hpp>
#include <boost/range/empty.hpp>
#include <pstade/candy/set.hpp>
#include <pstade/oven/null_terminate_range.hpp>
#include <pstade/oven/pointer_range.hpp>
#include <pstade/oven/sequence_cast.hpp>
#include <pstade/require.hpp>
#include "../diet/valid.hpp"
#include "../size_initialize.hpp"
#include "./get_rebar_band_info.hpp"


namespace pstade { namespace tomato {


inline // 'cx' can be 0.
void add_rebar_band(HWND hWndReBar, HWND hWndBand, UINT fStyle, const TCHAR *pszText, UINT cx)
{
	BOOST_ASSERT(diet::valid(hWndReBar));
	BOOST_ASSERT(diet::valid(hWndBand));
	BOOST_ASSERT(diet::valid(pszText));
	BOOST_ASSERT(::GetDlgCtrlID(hWndBand) != 0 && "pstade::tomato::add_rebar_band - child window id is invalid.");


	// info.lpText is not 'const'. 'const_cast' is dangerous.
	std::vector<TCHAR> text; {
		text = oven::sequence(pszText|oven::null_terminated);
		text.push_back('\0');
		BOOST_ASSERT(oven::is_null_terminated(text));
	}

	bool hasTitle = !boost::empty(text|oven::null_terminated);


	REBARBANDINFO info; {
		info|size_initialized;

#if (_WIN32_IE >= 0x0400)
		info.fMask = RBBIM_CHILD | RBBIM_CHILDSIZE | RBBIM_STYLE | RBBIM_ID | RBBIM_SIZE | RBBIM_IDEALSIZE;
#else
		info.fMask = RBBIM_CHILD | RBBIM_CHILDSIZE | RBBIM_STYLE | RBBIM_ID | RBBIM_SIZE;
#endif
		
		if (hasTitle)
			candy::set(info.fMask, RBBIM_TEXT);
		
		info.fStyle = fStyle;
		info.lpText = boost::begin(text|oven::pointed);
		info.hwndChild = hWndBand;
		info.wID = ::GetDlgCtrlID(hWndBand); // how's that

		info.cxMinChild = tomato::get_rebar_band_info_cxMinChild(hWndBand, hasTitle);
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
	} // info


	WTL::CReBarCtrl rebar(hWndReBar);
	PSTADE_REQUIRE(rebar.InsertBand(-1, &info));


/* should be?
#if (_WIN32_IE >= 0x0501)
		DWORD dwExStyle = (DWORD)::SendMessage(hWndBand, TB_GETEXTENDEDSTYLE, 0, 0L);
		::SendMessage(hWndBand, TB_SETEXTENDEDSTYLE, 0, dwExStyle | TBSTYLE_EX_HIDECLIPPEDBUTTONS);
#endif // (_WIN32_IE >= 0x0501)
*/

}


} } // namespace pstade::tomato


#endif
