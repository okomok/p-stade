#ifndef PSTADE_TOMATO_MENU_GET_MENU_ITEM_COUNT_HPP
#define PSTADE_TOMATO_MENU_GET_MENU_ITEM_COUNT_HPP


// PStade.Tomato
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// See:
//
// wec400/STANDARDSDK/Mfc/Src/wcealt.cpp


#include <pstade/apple/sdk/windows.hpp>
#include <pstade/static_c.hpp>
#include "../require.hpp"
#include "../size_initialize.hpp"
#include "./menu_ref.hpp"


namespace pstade { namespace tomato {


inline
int get_menu_item_count(menu_ref menu)
{
#if !defined(_WIN32_WCE)

    return ::GetMenuItemCount(menu);

#else

    typedef static_c<UINT, 256> max_item_count;

    MENUITEMINFO mii = { 0 };
    mii|size_initialize;

    int count = 0;
    for (UINT i = 0; i < max_item_count::value; ++i) {
        if (!::GetMenuItemInfo(menu, i, TRUE, &mii))
            break;

        ++count;
    }

    return count;

#endif // !defined(_WIN32_WCE)
}


} } // namespace pstade::tomato


#endif
