#pragma once

#include <pstade/tomato/window/register_window_message.hpp>
#include "./cmd_ui.hpp"

namespace pstade { namespace ketchup {


namespace update_cmd_ui_message_detail {

	struct tag { };

}


inline UINT id_update_cmd_ui_message()
{
	return tomato::register_window_message<update_cmd_ui_message_detail::tag>(_T("pstade_ketchup_update_cmd_ui"));
}


inline bool is_cmd_ui_handled(LRESULT lResult)
{
	return lResult == 1;
}


inline void set_cmd_ui_handled(LRESULT& lResult, bool handled)
{
	lResult = handled ? 1 : 0;
}


inline cmd_ui& wParam_to_cmd_ui(WPARAM wParam)
{
	cmd_ui *p_ui = reinterpret_cast<cmd_ui*>(wParam);
	return *p_ui;
}


inline WPARAM cmd_ui_to_wParam(cmd_ui& ui)
{
	return reinterpret_cast<WPARAM>(&ui);
}


} } // namespace pstade::ketchup
