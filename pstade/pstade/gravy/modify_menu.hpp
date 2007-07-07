#ifndef PSTADE_GRAVY_MODIFY_MENU_HPP
#define PSTADE_GRAVY_MODIFY_MENU_HPP


// PStade.Gravy
//
// Copyright Shunsuke Sogame 2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// See:
//
// wec400/STANDARDSDK/Mfc/Src/wcealt.cpp


#include <boost/assert.hpp>
#include <pstade/candy/set.hpp>
#include <pstade/pod_constant.hpp>
#include "./boolean_cast.hpp"
#include "./get_menu_item_count.hpp"
#include "./get_menu_item_id.hpp"
#include "./menu_ref.hpp"
#include "./sdk/tchar.hpp"
#include "./sdk/windows.hpp"


namespace pstade { namespace gravy {


    struct op_modify_menu
    {
        typedef bool result_type;

        bool operator()(menu_ref menu,
            UINT uPosition, UINT uFlags,
            UINT uIDNewItem = 0, TCHAR const *lpNewItem = NULL) const
        {
#if !defined(_WIN32_WCE)
            return ::ModifyMenu(menu, uPosition, uFlags, uIDNewItem, lpNewItem)|to_boolean;
#else
            // Handle MF_BYCOMMAND case; MF_BYCOMMAND is 0
            if ((uFlags & MF_BYPOSITION) != MF_BYPOSITION) {
                int count = gravy::get_menu_item_count(menu);
                int pos = 0;

                while (uPosition != gravy::get_menu_item_id(menu, pos) && (pos < count))
                    ++pos;

                BOOST_ASSERT(pos < count);

                uPosition = pos;
                candy::set(uFlags, MF_BYPOSITION);
            }

            if (!::DeleteMenu(menu, uPosition, uFlags))
                return false;

            return ::InsertMenu(menu, uPosition, uFlags, uIDNewItem, lpNewItem)|to_boolean;
#endif // !defined(_WIN32_WCE)
        }
    };


    PSTADE_POD_CONSTANT((op_modify_menu), modify_menu) = {};


} } // namespace pstade::gravy


#endif
