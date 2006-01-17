#pragma once

#include <pstade/tomato/diagnostic/is_valid.hpp>
#include "../impl/multipanestatusbar_cmd_ui.hpp"
#include "./update_cmd_ui.hpp"

namespace pstade { namespace ketchup {


template< class MultiPaneStatusBarCtrl > inline
void update_multipanestatusbar_cmd_ui(HWND hWndUpdater, MultiPaneStatusBarCtrl& statusbar)
{
	ATLASSERT(tomato::is_valid(hWndUpdater));
	ATLASSERT(tomato::is_valid(statusbar));

	for (int i = 0, count = statusbar.m_nPanes; i < count; ++i)
	{
		// get buttons state
		int id = statusbar.m_pPane[i];
		multipanestatusbar_cmd_ui<MultiPaneStatusBarCtrl> ui(id, statusbar, i);
		ketchup::update_cmd_ui(hWndUpdater, ui);
	}
}

} } // namespace pstade::ketchup

