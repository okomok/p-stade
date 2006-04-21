#ifndef PSTADE_KETCHUP_CMD_UI_UPDATE_MULTIPANESTATUSBAR_CMD_UI_HPP
#define PSTADE_KETCHUP_CMD_UI_UPDATE_MULTIPANESTATUSBAR_CMD_UI_HPP


// PStade.Ketchup
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/assert.hpp>
#include <boost/microsoft/sdk/windows.hpp>
#include <pstade/tomato/diet/valid.hpp>
#include "../impl/multipanestatusbar_cmd_ui.hpp"
#include "./cmd_ui.hpp"


namespace pstade { namespace ketchup {


template< class MultiPaneStatusBarCtrl > inline
void update_multipanestatusbar_cmd_ui(HWND hWndUpdater, MultiPaneStatusBarCtrl& statusbar)
{
    BOOST_ASSERT(diet::valid(hWndUpdater));
    BOOST_ASSERT(diet::valid(statusbar.m_hWnd));

    for (int i = 0, count = statusbar.m_nPanes; i < count; ++i)
    {
        // get buttons state
        int id = statusbar.m_pPane[i];
        multipanestatusbar_cmd_ui<MultiPaneStatusBarCtrl> ui(id, statusbar, i);
        ketchup::update_cmd_ui(hWndUpdater, ui);
    }
}

} } // namespace pstade::ketchup


#endif
