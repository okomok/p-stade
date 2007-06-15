#ifndef PSTADE_GRAVY_SET_MENU_CHECK_TYPE_HPP
#define PSTADE_GRAVY_SET_MENU_CHECK_TYPE_HPP


// PStade.Gravy
//
// Copyright Shunsuke Sogame 2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/scoped_array.hpp>
#include <pstade/candy/reset.hpp>
#include <pstade/candy/set.hpp>
#include <pstade/candy/test.hpp>
#include <pstade/constant.hpp>
#include <pstade/require.hpp>
#include <pstade/unused.hpp>
#include "./menu_ref.hpp"
#include "./sdk/windows.hpp"
#include "./size_initialize.hpp"


namespace pstade { namespace gravy {


    struct op_set_menu_check_type
    {
        typedef void result_type;

        void operator()(menu_ref menu, UINT uIndex, bool on) const
        {
#if !defined(_WIN32_WCE)

            MENUITEMINFO mii = { 0 }; {
                mii|size_initialized;
                mii.fMask = MIIM_TYPE;
                PSTADE_REQUIRE(::GetMenuItemInfo(menu, uIndex, TRUE, &mii));
            }

            if (on == candy::test(mii.fType, MFT_RADIOCHECK))
                return;

            boost::scoped_array<TCHAR> szString;

            if (// The case of MFT_STRING; MFT_STRING == 0, so...
                !candy::test(mii.fType, MFT_BITMAP) &&
                !candy::test(mii.fType, MFT_SEPARATOR) &&
                !candy::test(mii.fType, MFT_OWNERDRAW) // Win32 documentation is broken.
            ) {
                // get the menu_ref string
                szString.reset(new TCHAR[mii.cch + 1]);
                mii.dwTypeData = szString.get();
                ++mii.cch; 
                PSTADE_REQUIRE(::GetMenuItemInfo(menu, uIndex, TRUE, &mii));
            }

            if (on)
                candy::set(mii.fType, MFT_RADIOCHECK);
            else
                candy::reset(mii.fType, MFT_RADIOCHECK);

            PSTADE_REQUIRE(::SetMenuItemInfo(menu, uIndex, TRUE, &mii));

#else

            pstade::unused(menu, uIndex, on);

#endif // !defined(_WIN32_WCE)
        }
    };


    PSTADE_CONSTANT(set_menu_check_type, (op_set_menu_check_type))


} } // namespace pstade::gravy


#endif
