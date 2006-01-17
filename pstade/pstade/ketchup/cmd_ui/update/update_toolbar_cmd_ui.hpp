#pragma once

#include <atlctrls.h>
#include <pstade/candy/test.hpp>
#include <pstade/tomato/diagnostic/is_valid.hpp>
#include <pstade/tomato/diagnostic/verify.hpp>
#include "../impl/toolbar_cmd_ui.hpp"
#include "./update_cmd_ui.hpp"

namespace pstade { namespace ketchup {


inline void update_toolbar_cmd_ui(HWND hWndUpdater, HWND hWndToolBar)
{
	// See: MFC7::CToolBar::OnUpdateCmdUI

	ATLASSERT(tomato::is_valid(hWndUpdater));
	ATLASSERT(tomato::is_valid(hWndToolBar));

	WTL::CToolBarCtrl toolbar(hWndToolBar);
	for (int i = 0, count = toolbar.GetButtonCount(); i < count; ++i)
	{
		TBBUTTON button;
		tomato::api_verify(toolbar.GetButton(i, &button));
		UINT uID = button.idCommand;
		toolbar_cmd_ui ui(uID, toolbar);

		// ignore separators
		if (!candy::test(button.fsStyle, TBSTYLE_SEP))
			ketchup::update_cmd_ui(hWndUpdater, ui);
	}
}


} } // namespace pstade::ketchup
