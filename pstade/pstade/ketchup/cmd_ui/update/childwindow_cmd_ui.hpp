#ifndef PSTADE_KETCHUP_CMD_UI_UPDATE_CHILDWINDOW_CMD_UI_HPP
#define PSTADE_KETCHUP_CMD_UI_UPDATE_CHILDWINDOW_CMD_UI_HPP


// PStade.Ketchup
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/gravy/sdk/windows.hpp>
#include <pstade/gravy/window_ref.hpp>
#include "../impl/childwindow_cmd_ui.hpp"
#include "./cmd_ui.hpp"


namespace pstade { namespace ketchup {


inline
void update_childwindow_cmd_ui(gravy::window_ref updater, gravy::window_ref parent, UINT uID)
{
    gravy::window_ref child = ::GetDlgItem(parent, uID);

    childwindow_cmd_ui ui(uID, child);
    ketchup::update_cmd_ui(updater, ui);
}


} } // namespace pstade::ketchup


#endif
