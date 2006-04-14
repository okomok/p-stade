#ifndef PSTADE_TOMATO_TOOLBAR_CHECK_TOOLBAR_BUTTON_HPP
#define PSTADE_TOMATO_TOOLBAR_CHECK_TOOLBAR_BUTTON_HPP


// PStade.Tomato
//
// Copyright 2006 MB.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/assert.hpp>
#include <boost/microsoft/sdk/windows.hpp>
#include <boost/microsoft/wtl/ctrls.hpp> // CToolBarCtrl
#include <pstade/candy/remove.hpp>
#include <pstade/candy/set.hpp>
#include <pstade/candy/union.hpp>
#include <pstade/require.hpp>
#include "../diet/valid.hpp"
#include "../size_initialize.hpp"


namespace pstade { namespace tomato {


inline
void check_toolbar_button(HWND hWndToolBar, UINT uID, int state)
{
	BOOST_ASSERT(diet::valid(hWndToolBar));
	BOOST_ASSERT(0 <= state && state <= 2); // 0=>off, 1=>on, 2=>indeterminate

	WTL::CToolBarCtrl toolbar(hWndToolBar);

	TBBUTTONINFO tbb; {
		tbb|size_initialized;
		tbb.dwMask = TBIF_STATE | TBIF_STYLE;
		PSTADE_REQUIRE(toolbar.GetButtonInfo(uID, &tbb) != -1);
	}

	BYTE bOldStyle = tbb.fsStyle;
	BYTE bOldState = tbb.fsState;

	// TBSTYLE_XXX is wrongly defined as 'int'.

	// add check style
	candy::set(tbb.fsStyle, TBSTYLE_CHECK);

	// reset state and...
	candy::remove(tbb.fsState,
		// Topic: built-in operator| converts BYTE to int
		candy::union_(TBSTATE_CHECKED, TBSTATE_INDETERMINATE)
	);

	if (state == 1)
		candy::set(tbb.fsState, TBSTATE_CHECKED);
	else if (state == 2)
		candy::set(tbb.fsState, TBSTATE_INDETERMINATE);

	if (bOldStyle == tbb.fsStyle && bOldState == tbb.fsState)
		return;

	PSTADE_REQUIRE(toolbar.SetButtonInfo(uID, &tbb));
}


} } // namespace pstade::tomato


#endif
