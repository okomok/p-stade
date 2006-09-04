#ifndef PSTADE_TOMATO_TOOLBAR_CHECK_TOOLBAR_BUTTON_HPP
#define PSTADE_TOMATO_TOOLBAR_CHECK_TOOLBAR_BUTTON_HPP


// PStade.Tomato
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/assert.hpp>
#include <pstade/apple/sdk/windows.hpp>
#include <pstade/apple/wtl/ctrls.hpp> // CToolBarCtrl
#include <pstade/candy/remove.hpp>
#include <pstade/candy/set.hpp>
#include <pstade/candy/union.hpp>
#include <pstade/require.hpp>
#include "../size_initialize.hpp"
#include "../window/window_ref.hpp"


namespace pstade { namespace tomato {


inline
void check_toolbar_button(window_ref toolbar, UINT uID, int state)
{
    BOOST_ASSERT(0 <= state && state <= 2); // 0=>off, 1=>on, 2=>indeterminate

    WTL::CToolBarCtrl toolbars(toolbar);

    TBBUTTONINFO tbb; {
        tbb|size_initialized;
        tbb.dwMask = TBIF_STATE | TBIF_STYLE;
        PSTADE_REQUIRE(toolbars.GetButtonInfo(uID, &tbb) != -1);
    }

    BYTE bOldStyle = tbb.fsStyle;
    BYTE bOldState = tbb.fsState;

    // TBSTYLE_XXX is wrongly defined as 'int'.

    // add check style
    candy::set(tbb.fsStyle, TBSTYLE_CHECK);

    // reset state and...
    candy::remove(tbb.fsState,
        // Topic: built-in operator| converts BYTE to int
        candy::union_(TBSTATE_CHECKED, TBSTATE_INDETERMINATE)
    );

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
