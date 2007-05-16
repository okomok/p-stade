#ifndef PSTADE_HAMBURGER_DETAIL_REMOVE_CAPTION_HPP
#define PSTADE_HAMBURGER_DETAIL_REMOVE_CAPTION_HPP


// PStade.Hamburger
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// Note:
//
// Win32 adds caption forcefully when creating window.


#include <boost/microsoft/atl/win.hpp> // CWindow
#include <boost/microsoft/sdk/windows.hpp>
#include <boost/assert.hpp>
#include <pstade/tomato/diet/valid.hpp>
#include "../element.hpp"


namespace pstade { namespace hamburger { namespace detail {


inline
void remove_caption(HWND hWnd)
{
    BOOST_ASSERT(diet::valid(hWnd));

    ATL::CWindow wnd(hWnd);
    wnd.ModifyStyle(WS_CAPTION, 0);
    wnd.SetWindowPos(NULL, 0, 0, 0, 0, SWP_NOMOVE|SWP_NOSIZE|SWP_NOACTIVATE|SWP_NOZORDER|SWP_FRAMECHANGED);
}


} } } // namespace pstade::hamburger::detail


#endif
