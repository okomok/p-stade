#ifndef PSTADE_TOMATO_CHECK_TOOLBAR_BUTTON_HPP
#define PSTADE_TOMATO_CHECK_TOOLBAR_BUTTON_HPP


// PStade.Tomato
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/assert.hpp>
#include <pstade/candy/remove.hpp>
#include <pstade/candy/set.hpp>
#include <pstade/gravy/sdk/windows.hpp>
#include <pstade/gravy/size_initialize.hpp>
#include <pstade/gravy/window_ref.hpp>
#include <pstade/require.hpp>
#include "./wtl/ctrls.hpp" // CToolBarCtrl


namespace pstade { namespace tomato {


    inline
    void check_toolbar_button(gravy::window_ref toolbar, UINT uID, int state)
    {
        BOOST_ASSERT(0 <= state && state <= 2); // 0=>off, 1=>on, 2=>indeterminate

        WTL::CToolBarCtrl toolbars(toolbar);

        TBBUTTONINFO tbb; {
            tbb|gravy::size_initialize();
            tbb.dwMask = TBIF_STATE | TBIF_STYLE;
            PSTADE_REQUIRE(toolbars.GetButtonInfo(uID, &tbb) != -1);
        }

        BYTE bOldStyle = tbb.fsStyle;
        BYTE bOldState = tbb.fsState;

        // TBSTYLE_XXX is wrongly defined as 'int'.

        // add check style
        candy::set(tbb.fsStyle, TBSTYLE_CHECK);

        // reset state and...
        candy::remove(tbb.fsState, TBSTATE_CHECKED | TBSTATE_INDETERMINATE);

        if (state == 1)
            candy::set(tbb.fsState, TBSTATE_CHECKED);
        else if (state == 2)
            candy::set(tbb.fsState, TBSTATE_INDETERMINATE);

        if (bOldStyle == tbb.fsStyle && bOldState == tbb.fsState)
            return;

        PSTADE_REQUIRE(toolbars.SetButtonInfo(uID, &tbb));
    }


} } // namespace pstade::tomato


#endif
