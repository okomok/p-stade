#pragma once

#include <atlctrls.h>
#include <pstade/candy/add.hpp>
#include <pstade/candy/empty.hpp>
#include <pstade/candy/intersection.hpp>
#include <pstade/candy/remove.hpp>
#include "../diagnostic/is_valid.hpp"
#include "../diagnostic/verify.hpp"
#include "../structure/version_initialize.hpp"

namespace pstade { namespace tomato {


namespace modify_rebar_band_style_detail {

	struct rem_add
	{
		rem_add(UINT rem, UINT add) :
			m_uRemStyles(rem), m_uAddStyles(add)
		{ }

		void operator()(UINT& fStyle) const
		{
			candy::remove(fStyle, m_uRemStyles);
			candy::add(fStyle, m_uAddStyles);
		}

	private:
		UINT m_uRemStyles, m_uAddStyles;
	};

} // namespace modify_rebar_band_style_detail


template< class Functor >
Functor modify_rebar_band_style(HWND hWndReBar, UINT uBandID, Functor fun)
{
	ATLASSERT(tomato::is_valid(hWndReBar));

	WTL::CReBarCtrl rebar(hWndReBar);
	int index = rebar.IdToIndex(uBandID);
	ATLASSERT(index != -1 && "pstade::tomato::modify_rebar_band_style - band id is invalid.");

	REBARBANDINFO info;
	tomato::version_initialize(info);
	info.fMask = RBBIM_STYLE;
	tomato::api_verify(rebar.GetBandInfo(index, &info));

	fun(info.fStyle);

	tomato::api_verify(rebar.SetBandInfo(index, &info));

	return fun;
}


inline void modify_rebar_band_style(HWND hWndReBar, UINT uBandID, UINT uRemStyles, UINT uAddStyles)
{
	ATLASSERT(tomato::is_valid(hWndReBar));
	ATLASSERT(candy::empty(candy::intersection(uRemStyles, uAddStyles)));
	
	tomato::modify_rebar_band_style(
		hWndReBar, uBandID,
		modify_rebar_band_style_detail::rem_add(uRemStyles, uAddStyles)
	);
}


} } // namespace pstade::tomato
