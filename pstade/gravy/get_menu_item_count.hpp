#ifndef PSTADE_GRAVY_GET_MENU_ITEM_COUNT_HPP
#define PSTADE_GRAVY_GET_MENU_ITEM_COUNT_HPP


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
#include <pstade/static_c.hpp>
#include "./menu_ref.hpp"
#include "./sdk/windows.hpp"
#include "./size_initialize.hpp"


namespace pstade { namespace gravy {


    struct T_get_menu_item_count
    {
        typedef int result_type;

        int operator()(menu_ref menu) const
        {
#if !defined(_WIN32_WCE)
            return ::GetMenuItemCount(menu);
#else
            typedef static_c<UINT, 256> max_item_count;

            MENUITEMINFO mii = { 0 };
            mii|size_initialize();

            int count = 0;
            for (UINT i = 0; i < max_item_count::value; ++i) {
                if (!::GetMenuItemInfo(menu, i, TRUE, &mii))
                    break;

                ++count;
            }

            return count;
#endif // !defined(_WIN32_WCE)
        }
    };


    PSTADE_POD_CONSTANT((T_get_menu_item_count), get_menu_item_count) = {};


} } // namespace pstade::gravy


#endif
