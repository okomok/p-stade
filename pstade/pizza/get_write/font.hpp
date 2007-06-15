#ifndef PSTADE_PIZZA_GET_WRITE_FONT_HPP
#define PSTADE_PIZZA_GET_WRITE_FONT_HPP


// PStade.Pizza
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/apple/atl/win.hpp> // CWindow
#include <pstade/apple/sdk/windows.hpp>
#include <pstade/apple/wtl/gdi.hpp> // CLogFont
#include <pstade/require.hpp>
#include <pstade/gravy/window_ref.hpp>
#include "./logfont.hpp"


namespace pstade { namespace pizza {


template< class Profile >
void write_font(Profile& pr, gravy::window_ref wnd)
{
    HFONT hFont = ATL::CWindow(wnd).GetFont();
    if (hFont == NULL)
        return;

    pizza::write_logfont(pr, WTL::CLogFont(hFont));
}


// 'get_font' is impossible
// font handles must be managed by yourself.


} } // namespace pstade::pizza


#endif
