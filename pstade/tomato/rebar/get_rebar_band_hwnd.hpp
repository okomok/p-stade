#ifndef PSTADE_TOMATO_REBAR_GET_REBAR_BAND_HWND_HPP
#define PSTADE_TOMATO_REBAR_GET_REBAR_BAND_HWND_HPP


// PStade.Tomato
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/assert.hpp>
#include <pstade/apple/sdk/windows.hpp>
#include <pstade/apple/wtl/ctrls.hpp> // CReBarCtrl
#include <pstade/require.hpp>
#include "../diet/valid.hpp"
#include "../size_initialize.hpp"


namespace pstade { namespace tomato {


inline
HWND get_rebar_band_hwnd(HWND hWndReBar, UINT uBandID)
{
    BOOST_ASSERT(diet::valid(hWndReBar));
    
    WTL::CReBarCtrl rebar(hWndReBar);
    int index = rebar.IdToIndex(uBandID);
    // Note: RB_IDTOINDEX doesn't use GetLastError().
    BOOST_ASSERT("invalid band id" && index != -1);

    REBARBANDINFO info; {
        info|size_initialized;
        info.fMask = RBBIM_CHILD;
        PSTADE_REQUIRE(rebar.GetBandInfo(index, &info));
    }

    return info.hwndChild;
}


} } // namespace pstade::tomato


#endif
