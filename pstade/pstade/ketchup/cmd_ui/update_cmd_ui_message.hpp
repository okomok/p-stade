#ifndef PSTADE_KETCHUP_CMD_UI_UPDATE_CMD_UI_MESSAGE_HPP
#define PSTADE_KETCHUP_CMD_UI_UPDATE_CMD_UI_MESSAGE_HPP


// PStade.Ketchup
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/apple/sdk/tchar.hpp>
#include <pstade/apple/sdk/windows.hpp>
#include <pstade/tomato/window/register_window_message.hpp>
#include "./cmd_ui.hpp"


namespace pstade { namespace ketchup {


namespace update_cmd_ui_message_detail {

    PSTADE_TOMATO_REGISTER_WINDOW_MESSAGE(msg, pstade_ketchup_update_cmd_ui)

} // namespace update_cmd_ui_message_detail


inline
UINT id_update_cmd_ui_message()
{
    return update_cmd_ui_message_detail::msg;
}


inline
bool is_cmd_ui_handled(LRESULT lResult)
{
    return lResult == 1;
}


inline
void set_cmd_ui_handled(LRESULT& lResult, bool handled)
{
    lResult = handled ? 1 : 0;
}


inline
cmd_ui& wParam_to_cmd_ui(WPARAM wParam)
{
    cmd_ui *p_ui = reinterpret_cast<cmd_ui *>(wParam);
    return *p_ui;
}


inline
WPARAM cmd_ui_to_wParam(cmd_ui& ui)
{
    return reinterpret_cast<WPARAM>(&ui);
}


} } // namespace pstade::ketchup


#endif
