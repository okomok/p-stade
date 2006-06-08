#ifndef PSTADE_KETCHUP_CMD_UI_UPDATE_CHILDWINDOW_CMD_UI_HPP
#define PSTADE_KETCHUP_CMD_UI_UPDATE_CHILDWINDOW_CMD_UI_HPP


// PStade.Ketchup
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/assert.hpp>
#include <pstade/apple/sdk/windows.hpp>
#include <pstade/tomato/diet/valid.hpp>
#include "../impl/childwindow_cmd_ui.hpp"
#include "./cmd_ui.hpp"


namespace pstade { namespace ketchup {


inline
void update_childwindow_cmd_ui(HWND hWndUpdater, HWND hWndParent, UINT uID)
{
    BOOST_ASSERT(diet::valid(hWndUpdater));
    BOOST_ASSERT(diet::valid(hWndParent));

    HWND hWndChild = ::GetDlgItem(hWndParent, uID);
    BOOST_ASSERT(diet::valid(hWndChild));

    childwindow_cmd_ui ui(uID, hWndChild);
    ketchup::update_cmd_ui(hWndUpdater, ui);
}


} } // namespace pstade::ketchup


#endif
