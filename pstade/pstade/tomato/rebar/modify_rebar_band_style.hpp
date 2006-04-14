#ifndef PSTADE_TOMATO_REBAR_MODIFY_REBAR_BAND_STYLE_HPP
#define PSTADE_TOMATO_REBAR_MODIFY_REBAR_BAND_STYLE_HPP


// PStade.Tomato
//
// Copyright 2006 MB.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/assert.hpp>
#include <boost/microsoft/sdk/windows.hpp>
#include <boost/microsoft/wtl/ctrls.hpp> // CReBarCtrl
#include <pstade/candy/add.hpp>
#include <pstade/candy/empty.hpp>
#include <pstade/candy/intersection.hpp>
#include <pstade/candy/remove.hpp>
#include <pstade/require.hpp>
#include "../diet/valid.hpp"
#include "../size_initialize.hpp"


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
	BOOST_ASSERT(diet::valid(hWndReBar));

	WTL::CReBarCtrl rebar(hWndReBar);
	int index = rebar.IdToIndex(uBandID);
	BOOST_ASSERT(index != -1 && "pstade::tomato::modify_rebar_band_style - band id is invalid.");

	REBARBANDINFO info; {
		info|size_initialized;
		info.fMask = RBBIM_STYLE;
		PSTADE_REQUIRE(rebar.GetBandInfo(index, &info));
	}

	fun(info.fStyle);

	PSTADE_REQUIRE(rebar.SetBandInfo(index, &info));

	return fun;
}


inline
void modify_rebar_band_style(HWND hWndReBar, UINT uBandID, UINT uRemStyles, UINT uAddStyles)
{
	BOOST_ASSERT(diet::valid(hWndReBar));
	BOOST_ASSERT(candy::empty(candy::intersection(uRemStyles, uAddStyles)));
	
	tomato::modify_rebar_band_style(
		hWndReBar, uBandID,
		modify_rebar_band_style_detail::rem_add(uRemStyles, uAddStyles)
	);
}


} } // namespace pstade::tomato


#endif
