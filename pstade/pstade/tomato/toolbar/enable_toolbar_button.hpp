#ifndef PSTADE_TOMATO_TOOLBAR_ENABLE_TOOLBAR_BUTTON_HPP
#define PSTADE_TOMATO_TOOLBAR_ENABLE_TOOLBAR_BUTTON_HPP


// PStade.Tomato
//
// Copyright 2006 MB.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/assert.hpp>
#include <boost/microsoft/sdk/windows.hpp>
#include <boost/microsoft/wtl/ctrls.hpp> // CToolBarCtrl
#include <pstade/candy/reset.hpp>
#include <pstade/candy/set.hpp>
#include <pstade/require.hpp>
#include "../diet/valid.hpp"


namespace pstade { namespace tomato {


inline // See: MFC7::CToolCmdUI::Enable
void enable_toolbar_button(HWND hWndToolBar, UINT uID, bool on)
{
	BOOST_ASSERT(diet::valid(hWndToolBar));

	WTL::CToolBarCtrl toolbar(hWndToolBar);

	UINT uOldState = toolbar.GetState(uID);
	UINT uNewState = uOldState;

	BOOST_ASSERT(uNewState != -1);

	if (!on) {
		candy::reset(uNewState, TBSTATE_ENABLED);
		// WINBUG: If a button is currently pressed and then is disabled
		// COMCTL32.DLL does not unpress the button, even after the mouse
		// button goes up!  We work around this bug by forcing TBBS_PRESSED
		// off when a button is disabled.
		candy::reset(uNewState, TBSTATE_CHECKED);
	}
	else {
		candy::set(uNewState, TBSTATE_ENABLED);
	}

	if (uNewState == uOldState)
		return;

	PSTADE_REQUIRE(toolbar.SetState(uID, uNewState));
}


} } // namespace pstade::tomato


#endif
