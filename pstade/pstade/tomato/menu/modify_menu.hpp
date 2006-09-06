#ifndef PSTADE_TOMATO_MENU_MODIFY_MENU_HPP
#define PSTADE_TOMATO_MENU_MODIFY_MENU_HPP


// PStade.Tomato
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// See:
//
// wec400/STANDARDSDK/Mfc/Src/wcealt.cpp


#include <boost/assert.hpp>
#include <pstade/apple/sdk/tchar.hpp>
#include <pstade/apple/sdk/windows.hpp>
#include <pstade/candy/set.hpp>
#include "../boolean_cast.hpp"
#include "./get_menu_item_count.hpp"
#include "./get_menu_item_id.hpp"
#include "./menu_ref.hpp"


namespace pstade { namespace tomato {


inline
bool modify_menu(menu_ref menu,
    UINT uPosition, UINT uFlags,
    UINT uIDNewItem = 0, TCHAR const *lpNewItem = NULL)
{
#if !defined(_WIN32_WCE)

    return ::ModifyMenu(menu, uPosition, uFlags, uIDNewItem, lpNewItem)|booleanized;

#else

    // Handle MF_BYCOMMAND case; MF_BYCOMMAND is 0
    if ((uFlags & MF_BYPOSITION) != MF_BYPOSITION) {
        int count = tomato::get_menu_item_count(menu);
        int pos = 0;

        while (uPosition != tomato::get_menu_item_id(menu, pos) && (pos < count))
            ++pos;

        BOOST_ASSERT(pos < count);

        uPosition = pos;
        candy::set(uFlags, MF_BYPOSITION);
    }

    if (!::DeleteMenu(menu, uPosition, uFlags))
        return false;

    return ::InsertMenu(menu, uPosition, uFlags, uIDNewItem, lpNewItem)|booleanized;

#endif // !defined(_WIN32_WCE)
}


} } // namespace pstade::tomato


#endif
