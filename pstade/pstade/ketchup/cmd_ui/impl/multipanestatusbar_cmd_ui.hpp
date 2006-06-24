#ifndef PSTADE_KETCHUP_CMD_UI_IMPL_MULTIPANESTATUSBAR_CMD_UI_HPP
#define PSTADE_KETCHUP_CMD_UI_IMPL_MULTIPANESTATUSBAR_CMD_UI_HPP


// PStade.Ketchup
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/assert.hpp>
#include <pstade/apple/sdk/windows.hpp>
#include <pstade/tomato/diet/valid.hpp>
#include "../cmd_ui.hpp"


namespace pstade { namespace ketchup {


template< class MultiPaneStatusBarCtrl >
struct multipanestatusbar_cmd_ui : cmd_ui
{
    multipanestatusbar_cmd_ui(UINT nPaneID, MultiPaneStatusBarCtrl& statusbar, int index) :
        cmd_ui(nPaneID), m_statusbar(statusbar), m_index(index)
    {
        BOOST_ASSERT(diet::valid(statusbar.m_hWnd));
    }

private:
    void override_set_text(const TCHAR *pszText)
    {
        m_statusbar.SetPaneText(get_id(), pszText);
    }

private:
    MultiPaneStatusBarCtrl& m_statusbar;
    int m_index;
};


} } // namespace pstade::ketchup


#endif
