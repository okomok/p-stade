#ifndef PSTADE_KETCHUP_CMD_UI_UPDATE_TOOLBAR_CMD_UI_HPP
#define PSTADE_KETCHUP_CMD_UI_UPDATE_TOOLBAR_CMD_UI_HPP


// PStade.Ketchup
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/assert.hpp>
#include <pstade/apple/sdk/windows.hpp>
#include <pstade/apple/wtl/ctrls.hpp> // CToolBarCtrl
#include <pstade/candy/test.hpp>
#include <pstade/gravy/window_ref.hpp>
#include <pstade/require.hpp>
#include "../impl/toolbar_cmd_ui.hpp"
#include "./cmd_ui.hpp"


namespace pstade { namespace ketchup {


inline
void update_toolbar_cmd_ui(gravy::window_ref updater, gravy::window_ref toolbar)
{
    // See: MFC7::CToolBar::OnUpdateCmdUI

    for (int i = 0, count = WTL::CToolBarCtrl(toolbar).GetButtonCount(); i < count; ++i)
    {
        TBBUTTON button;
        PSTADE_REQUIRE(WTL::CToolBarCtrl(toolbar).GetButton(i, &button));
        UINT uID = button.idCommand;
        toolbar_cmd_ui ui(uID, toolbar);

        // ignore separators
        if (!candy::test(button.fsStyle, TBSTYLE_SEP))
            ketchup::update_cmd_ui(updater, ui);
    }
}


} } // namespace pstade::ketchup


#endif
