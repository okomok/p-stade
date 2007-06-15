#ifndef PSTADE_TOMATO_IS_FAMILY_TO_HPP
#define PSTADE_TOMATO_IS_FAMILY_TO_HPP


// PStade.Tomato
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// Todo:
//
// Move to gravy.


#include <pstade/gravy/window_ref.hpp>
#include "./atl/win.hpp" // CWindow


namespace pstade { namespace tomato {


    inline
    bool is_family_to(gravy::window_ref wnd1, gravy::window_ref wnd2)
    {
        if (wnd1 == wnd2)
            return true;

        return ATL::CWindow(wnd1).GetTopLevelParent()
            == ATL::CWindow(wnd2).GetTopLevelParent();
    }


} } // namespace pstade::tomato


#endif
