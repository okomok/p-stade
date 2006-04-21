#ifndef PSTADE_KETCHUP_CMD_UI_UPDATE_CMD_UI_HPP
#define PSTADE_KETCHUP_CMD_UI_UPDATE_CMD_UI_HPP


// PStade.Ketchup
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/assert.hpp>
#include <boost/microsoft/sdk/windows.hpp>
#include <pstade/tomato/diet/valid.hpp>
#include <pstade/tomato/window/send_message.hpp>
#include "../update_cmd_ui_message.hpp"


namespace pstade { namespace ketchup {


inline
bool update_cmd_ui(HWND hWndUpdater, cmd_ui& ui)
{
    BOOST_ASSERT(diet::valid(hWndUpdater));

    LRESULT lResult = tomato::send_message(hWndUpdater, ketchup::id_update_cmd_ui_message(), ketchup::cmd_ui_to_wParam(ui));
    return ketchup::is_cmd_ui_handled(lResult);
}


} } // namespace pstade::ketchup


#endif
