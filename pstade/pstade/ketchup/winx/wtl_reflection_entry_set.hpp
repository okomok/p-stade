#ifndef PSTADE_KETCHUP_WINX_WTL_REFLECTION_ENTRY_SET_HPP
#define PSTADE_KETCHUP_WINX_WTL_REFLECTION_ENTRY_SET_HPP


// PStade.Ketchup
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/mpl/void.hpp>
#include <pstade/apple/sdk/windows.hpp>
#include <pstade/unused.hpp>


namespace pstade { namespace ketchup {


struct wtl_reflection_entry_set
{

    template< class Dummy = boost::mpl::void_ >
    struct reflect_notifications_ex
    {
        template< class Derived >
        static bool process(Derived& derived, HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam, LRESULT& lResult, DWORD dwMsgMapID)
        {
            pstade::unused(derived, hWnd, uMsg, wParam, lParam, lResult, dwMsgMapID);

            BOOL bHandled = TRUE;
            lResult = derived.ReflectNotifications(uMsg, wParam, lParam, bHandled);
            if((lResult == 0) && (uMsg >= WM_CTLCOLORMSGBOX) && (uMsg <= WM_CTLCOLORSTATIC))
                bHandled = FALSE;
            if(bHandled)
                return true;

            return false;
        }
    };

    template< UINT uMsgFilter >
    struct reflect_notifications_msg_filtered
    {
        template< class Derived >
        static bool process(Derived& derived, HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam, LRESULT& lResult, DWORD dwMsgMapID)
        {
            pstade::unused(derived, hWnd, uMsg, wParam, lParam, lResult, dwMsgMapID);

            BOOL bHandled = TRUE;
            lResult = WTL::WtlReflectNotificationsFiltered(derived.m_hWnd, uMsg, wParam, lParam, bHandled, uMsgFilter, 0, NULL);
            if(bHandled)
                return true;

            return false;
        }
    };

    template< class F_idFromFilter >
    struct reflect_notifications_id_filtered
    {
        template< class Derived >
        static bool process(Derived& derived, HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam, LRESULT& lResult, DWORD dwMsgMapID)
        {
            pstade::unused(derived, hWnd, uMsg, wParam, lParam, lResult, dwMsgMapID);

            BOOL bHandled = TRUE;
            lResult = WTL::WtlReflectNotificationsFiltered(derived.m_hWnd, uMsg, wParam, lParam, bHandled, WM_NULL, F_idFromFilter()(derived), NULL);
            if(bHandled)
                return true;

            return false;
        }
    };

    template< class F_hWndChildFilter >
    struct reflect_notifications_hwnd_filtered
    {
        template< class Derived >
        static bool process(Derived& derived, HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam, LRESULT& lResult, DWORD dwMsgMapID)
        {
            pstade::unused(derived, hWnd, uMsg, wParam, lParam, lResult, dwMsgMapID);

            BOOL bHandled = TRUE;
            lResult = WTL::WtlReflectNotificationsFiltered(derived.m_hWnd, uMsg, wParam, lParam, bHandled, WM_NULL, 0, F_hWndChildFilter()(derived));
            if(bHandled)
                return true;

            return false;
        }
    };

    template< UINT uMsgFilter, class F_idFromFilter >
    struct reflect_notifications_msg_id_filtered
    {
        template< class Derived >
        static bool process(Derived& derived, HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam, LRESULT& lResult, DWORD dwMsgMapID)
        {
            pstade::unused(derived, hWnd, uMsg, wParam, lParam, lResult, dwMsgMapID);

            BOOL bHandled = TRUE;
            lResult = WTL::WtlReflectNotificationsFiltered(derived.m_hWnd, uMsg, wParam, lParam, bHandled, uMsgFilter, F_idFromFilter()(derived), NULL);
            if(bHandled)
                return true;

            return false;
        }
    };

    template< UINT uMsgFilter, class F_hWndChildFilter >
    struct reflect_notifications_msg_hwnd_filtered
    {
        template< class Derived >
        static bool process(Derived& derived, HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam, LRESULT& lResult, DWORD dwMsgMapID)
        {
            pstade::unused(derived, hWnd, uMsg, wParam, lParam, lResult, dwMsgMapID);

            BOOL bHandled = TRUE;
            lResult = WTL::WtlReflectNotificationsFiltered(derived.m_hWnd, uMsg, wParam, lParam, bHandled, uMsgFilter, 0, F_hWndChildFilter()(derived));
            if(bHandled)
                return true;

            return false;
        }
    };

    template< UINT id, UINT code >
    struct reflect_command
    {
        template< class Derived >
        static bool process(Derived& derived, HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam, LRESULT& lResult, DWORD dwMsgMapID)
        {
            pstade::unused(derived, hWnd, uMsg, wParam, lParam, lResult, dwMsgMapID);

            if(uMsg == WM_COMMAND && id == LOWORD(wParam) && code == HIWORD(wParam))
            {
                BOOL bHandled = TRUE;
                lResult = derived.ReflectNotifications(uMsg, wParam, lParam, bHandled);
                if(bHandled)
                    return true;
            }
            
            return false;
        }
    };

    template< UINT id >
    struct reflect_command_id
    {
        template< class Derived >
        static bool process(Derived& derived, HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam, LRESULT& lResult, DWORD dwMsgMapID)
        {
            pstade::unused(derived, hWnd, uMsg, wParam, lParam, lResult, dwMsgMapID);

            if(uMsg == WM_COMMAND && id == LOWORD(wParam))
            {
                BOOL bHandled = TRUE;
                lResult = derived.ReflectNotifications(uMsg, wParam, lParam, bHandled);
                if(bHandled)
                    return true;
            }
            
            return false;
        }
    };

    template< UINT code >
    struct reflect_command_code
    {
        template< class Derived >
        static bool process(Derived& derived, HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam, LRESULT& lResult, DWORD dwMsgMapID)
        {
            pstade::unused(derived, hWnd, uMsg, wParam, lParam, lResult, dwMsgMapID);

            if(uMsg == WM_COMMAND && code == HIWORD(wParam))
            {
                BOOL bHandled = TRUE;
                lResult = derived.ReflectNotifications(uMsg, wParam, lParam, bHandled);
                if(bHandled)
                    return true;
            }
            
            return false;
        }
    };

    template< UINT idFirst, UINT idLast >
    struct reflect_command_range
    {
        template< class Derived >
        static bool process(Derived& derived, HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam, LRESULT& lResult, DWORD dwMsgMapID)
        {
            pstade::unused(derived, hWnd, uMsg, wParam, lParam, lResult, dwMsgMapID);

            if(uMsg == WM_COMMAND && LOWORD(wParam) >= idFirst  && LOWORD(wParam) <= idLast)
            {
                BOOL bHandled = TRUE;
                lResult = derived.ReflectNotifications(uMsg, wParam, lParam, bHandled);
                if(bHandled)
                    return true;
            }
            
            return false;
        }
    };

    template< UINT idFirst, UINT idLast, UINT code >
    struct reflect_command_range_code
    {
        template< class Derived >
        static bool process(Derived& derived, HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam, LRESULT& lResult, DWORD dwMsgMapID)
        {
            pstade::unused(derived, hWnd, uMsg, wParam, lParam, lResult, dwMsgMapID);

            if(uMsg == WM_COMMAND && code == HIWORD(wParam) && LOWORD(wParam) >= idFirst  && LOWORD(wParam) <= idLast)
            {
                BOOL bHandled = TRUE;
                lResult = derived.ReflectNotifications(uMsg, wParam, lParam, bHandled);
                if(bHandled)
                    return true;
            }
            
            return false;
        }
    };

    template< UINT id, UINT cd >
    struct reflect_notify
    {
        template< class Derived >
        static bool process(Derived& derived, HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam, LRESULT& lResult, DWORD dwMsgMapID)
        {
            pstade::unused(derived, hWnd, uMsg, wParam, lParam, lResult, dwMsgMapID);

            if(uMsg == WM_NOTIFY && id == ((LPNMHDR)lParam)->idFrom && cd == ((LPNMHDR)lParam)->code)
            {
                BOOL bHandled = TRUE;
                lResult = derived.ReflectNotifications(uMsg, wParam, lParam, bHandled);
                if(bHandled)
                    return true;
            }
            
            return false;
        }
    };

    template< UINT id >
    struct reflect_notify_id
    {
        template< class Derived >
        static bool process(Derived& derived, HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam, LRESULT& lResult, DWORD dwMsgMapID)
        {
            pstade::unused(derived, hWnd, uMsg, wParam, lParam, lResult, dwMsgMapID);

            if(uMsg == WM_NOTIFY && id == ((LPNMHDR)lParam)->idFrom)
            {
                BOOL bHandled = TRUE;
                lResult = derived.ReflectNotifications(uMsg, wParam, lParam, bHandled);
                if(bHandled)
                    return true;
            }
            
            return false;
        }
    };

    template< UINT cd >
    struct reflect_notify_code
    {
        template< class Derived >
        static bool process(Derived& derived, HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam, LRESULT& lResult, DWORD dwMsgMapID)
        {
            pstade::unused(derived, hWnd, uMsg, wParam, lParam, lResult, dwMsgMapID);

            if(uMsg == WM_NOTIFY && cd == ((LPNMHDR)lParam)->code)
            {
                BOOL bHandled = TRUE;
                lResult = derived.ReflectNotifications(uMsg, wParam, lParam, bHandled);
                if(bHandled)
                    return true;
            }
            
            return false;
        }
    };

    template< UINT idFirst, UINT idLast >
    struct reflect_notify_range
    {
        template< class Derived >
        static bool process(Derived& derived, HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam, LRESULT& lResult, DWORD dwMsgMapID)
        {
            pstade::unused(derived, hWnd, uMsg, wParam, lParam, lResult, dwMsgMapID);

            if(uMsg == WM_NOTIFY && ((LPNMHDR)lParam)->idFrom >= idFirst && ((LPNMHDR)lParam)->idFrom <= idLast)
            {
                BOOL bHandled = TRUE;
                lResult = derived.ReflectNotifications(uMsg, wParam, lParam, bHandled);
                if(bHandled)
                    return true;
            }
            
            return false;
        }
    };

    template< UINT idFirst, UINT idLast, UINT cd >
    struct reflect_notify_range_code
    {
        template< class Derived >
        static bool process(Derived& derived, HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam, LRESULT& lResult, DWORD dwMsgMapID)
        {
            pstade::unused(derived, hWnd, uMsg, wParam, lParam, lResult, dwMsgMapID);

            if(uMsg == WM_NOTIFY && cd == ((LPNMHDR)lParam)->code && ((LPNMHDR)lParam)->idFrom >= idFirst && ((LPNMHDR)lParam)->idFrom <= idLast)
            {
                BOOL bHandled = TRUE;
                lResult = derived.ReflectNotifications(uMsg, wParam, lParam, bHandled);
                if(bHandled)
                    return true;
            }
            
            return false;
        }
    };

}; // struct wtl_reflection_entry_set


} } // namespace pstade::ketchup


#endif
