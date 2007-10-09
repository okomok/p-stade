#ifndef PSTADE_GRAVY_GET_MENU_ITEM_ID_HPP
#define PSTADE_GRAVY_GET_MENU_ITEM_ID_HPP


// PStade.Gravy
//
// Copyright Shunsuke Sogame 2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// See:
//
// wec400/STANDARDSDK/Mfc/Src/wcealt.cpp


#include <pstade/pod_constant.hpp>
#include <pstade/require.hpp>
#include "./menu_ref.hpp"
#include "./sdk/windows.hpp"
#include "./size_initialize.hpp"


namespace pstade { namespace gravy {


    struct T_get_menu_item_id
    {
        typedef UINT result_type;

        UINT operator()(menu_ref menu, int nPos) const
        {
#if !defined(_WIN32_WCE)
            return ::GetMenuItemID(menu, nPos);
#else
            MENUITEMINFO mii = { 0 }; {
                mii|size_initialize();
                mii.fMask  = MIIM_ID;
            }

            PSTADE_REQUIRE(::GetMenuItemInfo(menu, nPos, TRUE, &mii));
            return mii.wID; 
#endif // !defined(_WIN32_WCE)
        }
    };


    PSTADE_POD_CONSTANT((T_get_menu_item_id), get_menu_item_id) = {};


} } // namespace pstade::gravy


#endif
