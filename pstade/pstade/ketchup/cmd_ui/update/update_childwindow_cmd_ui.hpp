#pragma once

#include <pstade/tomato/diagnostic/is_valid.hpp>
#include "../impl/childwindow_cmd_ui.hpp"
#include "./update_cmd_ui.hpp"

namespace pstade { namespace ketchup {


inline void update_childwindow_cmd_ui(HWND hWndUpdater, HWND hWndParent, UINT uID)
{
	ATLASSERT(tomato::is_valid(hWndUpdater));
	ATLASSERT(tomato::is_valid(hWndParent));

	HWND hWndChild = ::GetDlgItem(hWndParent, uID);
	ATLASSERT(tomato::is_valid(hWndChild));

	childwindow_cmd_ui ui(uID, hWndChild);
	ketchup::update_cmd_ui(hWndUpdater, ui);
}


} } // namespace pstade::ketchup
