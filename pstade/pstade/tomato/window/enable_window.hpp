#ifndef PSTADE_TOMATO_WINDOW_ENABLE_WINDOW_HPP
#define PSTADE_TOMATO_WINDOW_ENABLE_WINDOW_HPP


// PStade.Tomato
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// See:
//
// 'CCmdUI::Enable' of MFC7


#include <pstade/apple/sdk/windows.hpp>
#include "./window_ptr.hpp"
#include "./window_ref.hpp"


namespace pstade { namespace tomato {


inline
void enable_window(window_ref wnd, bool on)
{
    // if control has the focus, move the focus before disabling
    if (!on && (::GetFocus() == wnd)) {
        window_ptr parent = ::GetParent(wnd);
        if (parent)
            ::SendMessage(*parent, WM_NEXTDLGCTL, 0, FALSE);
    }

    // never fails
    ::EnableWindow(wnd, on);
}


} } // namespace pstade::tomato


#endif
