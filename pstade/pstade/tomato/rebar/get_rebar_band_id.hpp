#ifndef PSTADE_TOMATO_REBAR_GET_REBAR_BAND_ID_HPP
#define PSTADE_TOMATO_REBAR_GET_REBAR_BAND_ID_HPP


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
UINT get_rebar_band_id(HWND hWndReBar, int index)
{
    BOOST_ASSERT(diet::valid(hWndReBar));

    WTL::CReBarCtrl rebar(hWndReBar);
    BOOST_ASSERT(0 <= index && index < rebar.GetBandCount());

    REBARBANDINFO info; {
        info|size_initialized;
        info.fMask = RBBIM_ID;
        PSTADE_REQUIRE(rebar.GetBandInfo(index, &info));
    }

    return info.wID;
}


} } // namespace pstade::tomato


#endif
