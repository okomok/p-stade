#pragma once

#include <pstade/tomato/diagnostic/is_valid.hpp>
#include <pstade/tomato/window/send_message.hpp>
#include "../update_cmd_ui_message.hpp"

namespace pstade { namespace ketchup {


inline bool update_cmd_ui(HWND hWndUpdater, cmd_ui& ui)
{
	ATLASSERT(tomato::is_valid(hWndUpdater));

	LRESULT lResult = tomato::send_message(hWndUpdater, ketchup::id_update_cmd_ui_message(), ketchup::cmd_ui_to_wParam(ui));
	return ketchup::is_cmd_ui_handled(lResult);
}


} } // namespace pstade::ketchup
