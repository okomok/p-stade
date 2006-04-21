#ifndef PSTADE_TOMATO_WINDOW_ENABLE_WINDOW_HPP
#define PSTADE_TOMATO_WINDOW_ENABLE_WINDOW_HPP


// PStade.Tomato
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// See:
//
// 'CCmdUI::Enable' of MFC7


#include <boost/assert.hpp>
#include <boost/microsoft/sdk/windows.hpp>
#include "../diet/valid.hpp"
#include "./send_message.hpp"


namespace pstade { namespace tomato {


inline
void enable_window(HWND hWnd, bool on)
{
    BOOST_ASSERT(diet::valid(hWnd));

    // if control has the focus, move the focus before disabling
    if (!on && (::GetFocus() == hWnd)) {
        HWND hWndParent = ::GetParent(hWnd);
        if (hWndParent != NULL)
            tomato::send_message(hWndParent, WM_NEXTDLGCTL, 0, FALSE);
    }

    // never fails
    ::EnableWindow(hWnd, on);
}


} } // namespace pstade::tomato


#endif
