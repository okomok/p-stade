#ifndef PSTADE_KETCHUP_CMD_UI_UPDATE_TOOLBAR_CMD_UI_HPP
#define PSTADE_KETCHUP_CMD_UI_UPDATE_TOOLBAR_CMD_UI_HPP


// PStade.Ketchup
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/assert.hpp>
#include <pstade/apple/sdk/windows.hpp>
#include <pstade/apple/wtl/ctrls.hpp> // CToolBarCtrl
#include <pstade/candy/test.hpp>
#include <pstade/require.hpp>
#include <pstade/tomato/diet/valid.hpp>
#include "../impl/toolbar_cmd_ui.hpp"
#include "./cmd_ui.hpp"


namespace pstade { namespace ketchup {


inline
void update_toolbar_cmd_ui(HWND hWndUpdater, HWND hWndToolBar)
{
    // See: MFC7::CToolBar::OnUpdateCmdUI

    BOOST_ASSERT(diet::valid(hWndUpdater));
    BOOST_ASSERT(diet::valid(hWndToolBar));

    WTL::CToolBarCtrl toolbar(hWndToolBar);
    for (int i = 0, count = toolbar.GetButtonCount(); i < count; ++i)
    {
        TBBUTTON button;
        PSTADE_REQUIRE(toolbar.GetButton(i, &button));
        UINT uID = button.idCommand;
        toolbar_cmd_ui ui(uID, toolbar);

        // ignore separators
        if (!candy::test(button.fsStyle, TBSTYLE_SEP))
            ketchup::update_cmd_ui(hWndUpdater, ui);
    }
}


} } // namespace pstade::ketchup


#endif
