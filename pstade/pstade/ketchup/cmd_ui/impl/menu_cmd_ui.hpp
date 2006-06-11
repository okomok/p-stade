#ifndef PSTADE_KETCHUP_CMD_UI_IMPL_MENU_CMD_UI_HPP
#define PSTADE_KETCHUP_CMD_UI_IMPL_MENU_CMD_UI_HPP


// PStade.Ketchup
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/assert.hpp>
#include <pstade/apple/sdk/tchar.hpp>
#include <pstade/apple/sdk/windows.hpp>
#include <pstade/require.hpp>
#include <pstade/tomato/diet/valid.hpp>
#include <pstade/tomato/menu/set_menu_check_type.hpp>
#include <pstade/tomato/menu/set_menu_default_item.hpp>
#include <pstade/tomato/menu/set_menu_text.hpp>
#include <pstade/tomato/menu/mf_disabled_value.hpp>
#include "../cmd_ui.hpp"


namespace pstade { namespace ketchup {


struct menu_cmd_ui : cmd_ui
{
    HMENU get_menu() const { return m_hMenu; }
    UINT get_index() const { return m_uIndex; }

    explicit menu_cmd_ui(UINT uID, HMENU hMenu, UINT uIndex, bool dependent) :
        cmd_ui(uID), m_hMenu(hMenu), m_uIndex(uIndex), m_dependent(dependent)
    {
        BOOST_ASSERT(diet::valid(m_hMenu));
    }

private:
    void override_enable(bool on)
    {
        ::EnableMenuItem(m_hMenu, m_uIndex, MF_BYPOSITION |
            (on ? MF_ENABLED : (tomato::mf_disabled::value | MF_GRAYED)));
    }

    void override_set_check(int state)
    {
        tomato::set_menu_check_type(m_hMenu, m_uIndex, false);

        ::CheckMenuItem(m_hMenu, m_uIndex, MF_BYPOSITION |
            (state ? MF_CHECKED : MF_UNCHECKED));
    }

#if !defined(_WIN32_WCE)
    void override_set_radio(bool on)
    {
        tomato::set_menu_check_type(m_hMenu, m_uIndex, true);

        ::CheckMenuItem(m_hMenu, m_uIndex, MF_BYPOSITION |
            (on ? MF_CHECKED : MF_UNCHECKED));
    }
#endif // !defined(_WIN32_WCE)

    void override_set_text(const TCHAR *pszText)
    {
        BOOST_ASSERT(diet::valid(pszText));

        tomato::set_menu_text(m_hMenu, m_uIndex, pszText);
    }

    void override_set_default(bool on)
    {
        // place checkmark next to menu item
        if (on)
            PSTADE_REQUIRE(tomato::set_menu_default_item(m_hMenu, m_uIndex, TRUE));
    }

    bool override_is_dependent()
    {
        return m_dependent;
    }

private:
    HMENU m_hMenu;
    UINT m_uIndex;
    bool m_dependent;
};


} } // namespace pstade::ketchup


#endif
