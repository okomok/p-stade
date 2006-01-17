#pragma once

#include <atlctrls.h>
#include <boost/config.hpp>
#include <boost/mpl/integral_c.hpp>
#include <pstade/candy/set.hpp>
#include <pstade/candy/remove.hpp>
#include <pstade/candy/reset.hpp>
#include <pstade/candy/union.hpp>
#include <pstade/tomato/diagnostic/is_valid.hpp>
#include <pstade/tomato/diagnostic/verify.hpp>
#include <pstade/tomato/structure/version_initialize.hpp>
#include "../cmd_ui.hpp"

namespace pstade { namespace ketchup {


struct toolbar_cmd_ui : cmd_ui
{
	toolbar_cmd_ui(UINT uID, HWND hWnd) :
		cmd_ui(uID), m_toolbar(hWnd)
	{
		ATLASSERT(tomato::is_valid(hWnd));
	}

protected:
	virtual void enable_impl(bool on)
	{
		// See: See: MFC7::CToolCmdUI::Enable

		UINT uOldState = m_toolbar.GetState(get_id());
		UINT uNewState = uOldState;
		ATLASSERT(uNewState != -1);
		if (!on)
		{
			candy::reset(uNewState, TBSTATE_ENABLED);
			// WINBUG: If a button is currently pressed and then is disabled
			// COMCTL32.DLL does not unpress the button, even after the mouse
			// button goes up!  We work around this bug by forcing TBBS_PRESSED
			// off when a button is disabled.
			candy::reset(uNewState, TBSTATE_CHECKED);
		}
		else
		{
			candy::set(uNewState, TBSTATE_ENABLED);
		}

		if (uNewState == uOldState)
			return;

		tomato::api_verify(m_toolbar.SetState(get_id(), uNewState));
	}

	virtual void set_check_impl(int state)
	{
		ATLASSERT(0 <= state && state <= 2); // 0=>off, 1=>on, 2=>indeterminate

		TBBUTTONINFO tbb;
		{
			tomato::version_initialize(tbb);
			tbb.dwMask = TBIF_STATE | TBIF_STYLE;
			tomato::api_verify( m_toolbar.GetButtonInfo(get_id(), &tbb) != -1 );
		}

		BYTE bOldStyle = tbb.fsStyle;
		BYTE bOldState = tbb.fsState;

		// Workaround:
		//   TBSTYLE_XXX is defined as 'int' wrongly.
		//   Explicit template parameters suppress the warnings.

		// add check style
		candy::set<BYTE, BYTE>(tbb.fsStyle, TBSTYLE_CHECK);

		// reset state and...
		candy::remove(tbb.fsState,
			// Note: built-in operator| converts BYTE to int
			candy::union_<BYTE, BYTE>(TBSTATE_CHECKED, TBSTATE_INDETERMINATE));

		if (state == 1)
			candy::set<BYTE, BYTE>(tbb.fsState, TBSTATE_CHECKED);
		else if (state == 2)
			candy::set<BYTE, BYTE>(tbb.fsState, TBSTATE_INDETERMINATE);

		if (bOldStyle == tbb.fsStyle && bOldState == tbb.fsState)
			return;

		tomato::api_verify(m_toolbar.SetButtonInfo(get_id(), &tbb));
	}

private:
	WTL::CToolBarCtrl m_toolbar;
};


} } // namespace pstade::ketchup
