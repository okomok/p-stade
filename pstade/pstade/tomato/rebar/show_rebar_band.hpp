#ifndef PSTADE_TOMATO_REBAR_SHOW_REBAR_BAND_HPP
#define PSTADE_TOMATO_REBAR_SHOW_REBAR_BAND_HPP


// PStade.Tomato
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/assert.hpp>
#include <boost/microsoft/sdk/windows.hpp>
#include <boost/microsoft/wtl/ctrls.hpp> // CReBarCtrl
#include <pstade/require.hpp>
#include "../diet/valid.hpp"


namespace pstade { namespace tomato {


inline
void show_rebar_band(HWND hWndReBar, UINT uBandID, bool visible)
{
    BOOST_ASSERT(diet::valid(hWndReBar));

    WTL::CReBarCtrl rebar(hWndReBar);
    int index = rebar.IdToIndex(uBandID);
    BOOST_ASSERT(index != -1 && "invalid band id");

    PSTADE_REQUIRE(rebar.ShowBand(index, visible));
}


} } // namespace pstade::tomato


#endif
