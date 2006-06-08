#ifndef PSTADE_KETCHUP_FRAME_ENTRY_SUBSET_HPP
#define PSTADE_KETCHUP_FRAME_ENTRY_SUBSET_HPP


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


struct frame_entry_subset
{

    template< class Dummy = boost::mpl::void_ >
    struct chain_client_commands
    {
        template< class Derived >
        static bool process(Derived& derived, HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam, LRESULT& lResult, DWORD dwMsgMapID)
        {
            pstade::unused(derived, hWnd, uMsg, wParam, lParam, lResult, dwMsgMapID);

            if (uMsg == WM_COMMAND)
            {
                HWND hWnd = derived.m_hWndClient;
                if (hWnd != NULL)
                    ::SendMessage(hWnd, uMsg, wParam, lParam);
                return false;
            }

            return false;
        }
    };

    template< class Dummy = boost::mpl::void_ >
    struct chain_mdi_child_commands
    {
        template< class Derived >
        static bool process(Derived& derived, HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam, LRESULT& lResult, DWORD dwMsgMapID)
        {
            pstade::unused(derived, hWnd, uMsg, wParam, lParam, lResult, dwMsgMapID);

            if (uMsg == WM_COMMAND)
            {
                HWND hWndChild = derived.MDIGetActive();
                if (hWndChild != NULL)
                    ::SendMessage(hWndChild, uMsg, wParam, lParam);
                return false;
            }

            return false;
        }
    };

};


} } // namespace pstade::ketchup


#endif
