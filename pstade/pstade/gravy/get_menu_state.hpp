#ifndef PSTADE_GRAVY_GET_MENU_STATE_HPP
#define PSTADE_GRAVY_GET_MENU_STATE_HPP


// PStade.Gravy
//
// Copyright Shunsuke Sogame 2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// See:
//
// wec400/STANDARDSDK/Mfc/Src/wcealt.cpp


#include <pstade/candy/test.hpp>
#include <pstade/pod_constant.hpp>
#include <pstade/require.hpp>
#include "./menu_ref.hpp"
#include "./sdk/windows.hpp"
#include "./size_initialize.hpp"


namespace pstade { namespace gravy {


    struct T_get_menu_state
    {
        typedef UINT result_type;

        UINT operator()(menu_ref menu, UINT uId, UINT uFlags) const
        {
#if !defined(_WIN32_WCE)
            return ::GetMenuState(menu, uId, uFlags);
#else
            MENUITEMINFO mii = { 0 }; {
                mii|size_initialize();
                mii.fMask  = MIIM_STATE;
            }

            if (candy::test(uFlags, MF_BYPOSITION))
                PSTADE_REQUIRE(::GetMenuItemInfo(menu, uId, TRUE, &mii));
            else
                PSTADE_REQUIRE(::GetMenuItemInfo(menu, uId, FALSE, &mii));

            return mii.fState;
#endif // !defined(_WIN32_WCE)
        }
    };


    PSTADE_POD_CONSTANT((T_get_menu_state), get_menu_state) = {};


} } // namespace pstade::gravy


#endif
