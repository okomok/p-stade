#ifndef PSTADE_TOMATO_WINDOW_IS_FAMILY_TO_HPP
#define PSTADE_TOMATO_WINDOW_IS_FAMILY_TO_HPP


// PStade.Tomato
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/apple/atl/win.hpp> // CWindow
#include "./window_ref.hpp"


namespace pstade { namespace tomato {


inline
bool is_family_to(window_ref wnd1, window_ref wnd2)
{
    if (wnd1 == wnd2)
        return true;

    return ATL::CWindow(wnd1).GetTopLevelParent()
        == ATL::CWindow(wnd2).GetTopLevelParent();
}


} } // namespace pstade::tomato


#endif
