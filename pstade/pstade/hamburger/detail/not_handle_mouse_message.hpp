#ifndef PSTADE_HAMBURGER_DETAIL_USING_MOUSE_MESSAGE_HPP
#define PSTADE_HAMBURGER_DETAIL_USING_MOUSE_MESSAGE_HPP


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
struct using_mouse_message
{
    template< class Derived > static
    bool process(Derived& derived, HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam, LRESULT& lResult, DWORD dwMsgMapID)
    {
        if (uMsg != WM_NCHITTEST)
            return false;

        lResult = HTCLIENT;
        pstade::unused(derived, hWnd, wParam, lParam, dwMsgMapID);
        return true;
    }
};


} } } // namespace pstade::hamburger::detail


#endif
