#ifndef PSTADE_KETCHUP_CMD_UI_COMPATIBILITY_HPP
#define PSTADE_KETCHUP_CMD_UI_COMPATIBILITY_HPP


// PStade.Ketchup
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/assert.hpp>
#include <boost/microsoft/sdk/windows.hpp>
#include "./update_cmd_ui_message.hpp"


namespace pstade { namespace ketchup {


inline
bool chain_mdi_child_cmd_ui_(HWND hWndMDIChild, UINT uMsg, WPARAM wParam, LPARAM lParam, LRESULT& lResult, DWORD)
{
    BOOST_ASSERT(uMsg == ketchup::id_update_cmd_ui_message());

    if (hWndMDIChild != NULL)
    {
        lResult = ::SendMessage(hWndMDIChild, uMsg, wParam, lParam);
        return ketchup::is_cmd_ui_handled(lResult);
    }
    return false;
}


} } // namespace pstade::ketchup


#define PSTADE_KETCHUP_CMD_UI_HANDLER(id, func) \
    if (uMsg == pstade::ketchup::id_update_cmd_ui_message()) \
    { \
        pstade::ketchup::cmd_ui& ui = pstade::ketchup::wParam_to_cmd_ui(wParam); \
        if (ui.get_id() == id) \
        { \
            ui.set_handled(true); \
            func(ui); \
            if (ui.is_handled()) \
            { \
                pstade::ketchup::set_cmd_ui_handled(lResult, true); \
                return TRUE; \
            } \
        } \
    } \
/**/


#define PSTADE_KETCHUP_INDEPENDENT_CMD_UI_HANDLER(id, func) \
    if (uMsg == pstade::ketchup::id_update_cmd_ui_message()) \
    { \
        pstade::ketchup::cmd_ui& ui = pstade::ketchup::wParam_to_cmd_ui(wParam); \
        if (ui.get_id() == id && !ui.is_dependent()) \
        { \
            ui.set_handled(true); \
            func(ui); \
            if (ui.is_handled()) \
            { \
                pstade::ketchup::set_cmd_ui_handled(lResult, true); \
                return TRUE; \
            } \
        } \
    } \
/**/


#define PSTADE_KETCHUP_DEPENDENT_CMD_UI_HANDLER(id, func) \
    if (uMsg == pstade::ketchup::id_update_cmd_ui_message()) \
    { \
        ketchup::cmd_ui& ui = pstade::ketchup::wParam_to_cmd_ui(wParam); \
        if (ui.get_id() == id && ui.is_dependent()) \
        { \
            ui.set_handled(true); \
            func(ui); \
            if (ui.is_handled()) \
            { \
                pstade::ketchup::set_cmd_ui_handled(lResult, true); \
                return TRUE; \
            } \
        } \
    } \
/**/


#define PSTADE_KETCHUP_CHAIN_CLIENT_CMD_UI() \
    if (uMsg == pstade::ketchup::id_update_cmd_ui_message()) \
    { \
        HWND hWndClient = m_hWndClient; \
        if (hWndClient != NULL) \
        { \
            lResult = ::SendMessage(hWndClient, uMsg, wParam, lParam); \
            if (pstade::ketchup::is_cmd_ui_handled(lResult)) \
                return TRUE; \
        } \
    } \
/**/


#define PSTADE_KETCHUP_CHAIN_MDI_CHILD_CMD_UI() \
    if (uMsg == pstade::ketchup::id_update_cmd_ui_message()) \
    { \
        HWND hWndActive = MDIGetActive(); \
        if (hWndActive != NULL) \
        { \
            lResult = ::SendMessage(hWndActive, uMsg, wParam, lParam); \
            if (pstade::ketchup::is_cmd_ui_handled(lResult)) \
                return TRUE; \
        } \
    } \
/**/


#define PSTADE_KETCHUP_ENABLE_CMD_UI_IF_HANDLED(proc, ids) \
    if (uMsg == ketchup::id_update_cmd_ui_message()) \
    { \
        bool cmd_ui_handled = proc(hWnd, uMsg, wParam, lParam, lResult, dwMsgMapID); \
        pstade::ketchup::cmd_ui& ui = pstade::ketchup::wParam_to_cmd_ui(wParam); \
        if (ids::contains(ui.get_id())) \
            ui.enable(cmd_ui_handled); \
        if (cmd_ui_handled) \
            return TRUE; \
    } \
/**/


#define PSTADE_KETCHUP_ENABLE_CMD_UI_IF_HANDLED_BY_MDI_CHILD(ids) \
    if (uMsg == pstade::ketchup::id_update_cmd_ui_message()) \
    { \
        HWND hWndActive = MDIGetActive(); \
        bool cmd_ui_handled = pstade::ketchup::chain_mdi_child_cmd_ui_(hWndActive, uMsg, wParam, lParam, lResult, dwMsgMapID); \
        pstade::ketchup::cmd_ui& ui = pstade::ketchup::wParam_to_cmd_ui(wParam); \
        if (ids::contains(ui.get_id())) \
            ui.enable(cmd_ui_handled); \
        if (cmd_ui_handled) \
            return TRUE; \
    } \
/**/


#define PSTADE_KETCHUP_UPDATE_MENU_CMD_UI() \
    if (uMsg == WM_INITMENUPOPUP) \
    { \
        pstade::ketchup::update_menu_cmd_ui(hWnd, reinterpret_cast<HMENU>(wParam)); \
    } \
/**/


#endif
