#ifndef PSTADE_TOMATO_REBAR_GET_REBAR_BAND_ID_HPP
#define PSTADE_TOMATO_REBAR_GET_REBAR_BAND_ID_HPP


// PStade.Tomato
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/assert.hpp>
#include <pstade/apple/sdk/windows.hpp>
#include <pstade/apple/wtl/ctrls.hpp> // CReBarCtrl
#include <pstade/contract.hpp>
#include <pstade/require.hpp>
#include <pstade/value_convert.hpp>
#include "../window/window_ref.hpp"
#include "../size_initialize.hpp"


namespace pstade { namespace tomato {


inline
UINT get_rebar_band_id(window_ref rebar, int index)
{
    WTL::CReBarCtrl rebars(rebar);

    PSTADE_PRECONDITION (
        (0 <= index)
        (pstade::value_convert<UINT>(index) < rebars.GetBandCount())
    )

    REBARBANDINFO info; {
        info|size_initialized;
        info.fMask = RBBIM_ID;
        PSTADE_REQUIRE(rebars.GetBandInfo(index, &info));
    }

    return info.wID;
}


} } // namespace pstade::tomato


#endif
