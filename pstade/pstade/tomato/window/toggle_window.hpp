#ifndef PSTADE_TOMATO_WINDOW_TOGGLE_WINDOW_HPP
#define PSTADE_TOMATO_WINDOW_TOGGLE_WINDOW_HPP


// PStade.Tomato
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/apple/sdk/windows.hpp>
#include "../boolean_cast.hpp"
#include "./window_ref.hpp"


namespace pstade { namespace tomato {


inline
bool toggle_window(window_ref wnd)
{
    BOOL bVisible = !::IsWindowVisible(wnd);
    ::ShowWindow(wnd, bVisible ? SW_SHOWNOACTIVATE : SW_HIDE);

    return bVisible|to_boolean;
}


} } // namespace pstade::tomato


#endif
