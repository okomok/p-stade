#ifndef PSTADE_HAMBURGER_DETAIL_HANDLE_WM_ERASEBKGND_HPP
#define PSTADE_HAMBURGER_DETAIL_HANDLE_WM_ERASEBKGND_HPP


// PStade.Hamburger
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/apple/sdk/windows.hpp>
#include <pstade/unused.hpp>


namespace pstade { namespace hamburger { namespace detail {


    template< class = void >
    struct handle_wm_erasebkgnd
    {
        template< class Derived > static
        bool process(Derived& derived, HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam, LRESULT& lResult, DWORD dwMsgMapID)
        {
            if (uMsg != WM_ERASEBKGND)
                return false;

            lResult = 1;
            pstade::unused(derived, hWnd, wParam, lParam, dwMsgMapID);
            return true;     
        }
    };


} } } // namespace pstade::hamburger::detail


#endif
