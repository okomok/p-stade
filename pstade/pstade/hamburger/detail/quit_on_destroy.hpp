#ifndef PSTADE_HAMBURGER_DETAIL_QUIT_ON_DESTROY_HPP
#define PSTADE_HAMBURGER_DETAIL_QUIT_ON_DESTROY_HPP


// PStade.Hamburger
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/gravy/sdk/windows.hpp>


namespace pstade { namespace hamburger { namespace detail {


    template< class = void >
    struct quit_on_destroy
    {
        template< class Derived > static
        bool process(Derived& derived, HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam, LRESULT& lResult, DWORD dwMsgMapID)
        {
            if (uMsg != WM_DESTROY)
                return false;

            ::PostQuitMessage(1);

            pstade::unused(derived, hWnd, wParam, lParam, lResult, dwMsgMapID);
            return false;
        }
    };



} } } // namespace pstade::hamburger::detail


#endif
