#ifndef PSTADE_TOMATO_REBAR_IS_REBAR_BAND_VISIBLE_HPP
#define PSTADE_TOMATO_REBAR_IS_REBAR_BAND_VISIBLE_HPP


// PStade.Tomato
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/assert.hpp>
#include <boost/microsoft/sdk/windows.hpp>
#include <boost/microsoft/wtl/ctrls.hpp> // CReBarCtrl
#include <pstade/candy/test.hpp>
#include <pstade/require.hpp>
#include "../diet/valid.hpp"
#include "../size_initialize.hpp"


namespace pstade { namespace tomato {


inline
bool is_rebar_band_visible(HWND hWndReBar, UINT uBandID)
{
    BOOST_ASSERT(diet::valid(hWndReBar));

    WTL::CReBarCtrl rebar(hWndReBar);
    int index = rebar.IdToIndex(uBandID);
    BOOST_ASSERT(index != -1 && "invalid band id");

    REBARBANDINFO info; {
        info|size_initialized;
        info.fMask = RBBIM_STYLE;
        PSTADE_REQUIRE(rebar.GetBandInfo(index, &info));
    }

    return !candy::test(info.fStyle, RBBS_HIDDEN);
}


} } // namespace pstade::tomato


#endif
