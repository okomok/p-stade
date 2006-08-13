#ifndef PSTADE_TOMATO_WINDOW_IS_FAMILY_TO_HPP
#define PSTADE_TOMATO_WINDOW_IS_FAMILY_TO_HPP


// PStade.Tomato
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/assert.hpp>
#include <pstade/apple/atl/win.hpp> // CWindow
#include <pstade/apple/sdk/windows.hpp>
#include "../diet/valid.hpp"


namespace pstade { namespace tomato {


inline
bool is_family_to(HWND hWnd0, HWND hWnd1)
{
    BOOST_ASSERT(diet::valid(hWnd0));
    BOOST_ASSERT(diet::valid(hWnd1));

    if (hWnd0 == hWnd1)
        return true;

    ATL::CWindow wnd0(hWnd0);
    ATL::CWindow wnd1(hWnd1);

    return wnd0.GetTopLevelParent() == wnd1.GetTopLevelParent();
}


} } // namespace pstade::tomato


#endif
