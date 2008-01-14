#ifndef PSTADE_KETCHUP_CMD_UI_IMPL_TOOLBAR_CMD_UI_HPP
#define PSTADE_KETCHUP_CMD_UI_IMPL_TOOLBAR_CMD_UI_HPP


// PStade.Ketchup
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/assert.hpp>
#include <pstade/gravy/sdk/windows.hpp>
#include <pstade/gravy/window_ref.hpp>
#include <pstade/tomato/enable_toolbar_button.hpp>
#include <pstade/tomato/check_toolbar_button.hpp>
#include "../cmd_ui.hpp"


namespace pstade { namespace ketchup {


struct toolbar_cmd_ui : cmd_ui
{
    toolbar_cmd_ui(UINT uID, gravy::window_ref toolbar) :
        cmd_ui(uID), m_toolbar(toolbar)
    { }

protected:
    void override_enable(bool on)
    {
        tomato::enable_toolbar_button(m_toolbar, get_id(), on);
    }

    void override_set_check(int state)
    {
        BOOST_ASSERT(0 <= state && state <= 2); // 0=>off, 1=>on, 2=>indeterminate
        tomato::check_toolbar_button(m_toolbar, get_id(), state);
    }

private:
    gravy::window_ref m_toolbar;
};


} } // namespace pstade::ketchup


#endif
