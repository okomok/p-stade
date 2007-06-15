#ifndef PSTADE_TOMATO_GET_REBAR_BAND_ID_HPP
#define PSTADE_TOMATO_GET_REBAR_BAND_ID_HPP


// PStade.Tomato
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/assert.hpp>
#include <pstade/contract.hpp>
#include <pstade/copy_construct.hpp>
#include <pstade/gravy/sdk/windows.hpp>
#include <pstade/gravy/size_initialize.hpp>
#include <pstade/gravy/window_ref.hpp>
#include <pstade/require.hpp>
#include "./wtl/ctrls.hpp" // CReBarCtrl


namespace pstade { namespace tomato {


    inline
    UINT get_rebar_band_id(gravy::window_ref rebar, int index)
    {
        WTL::CReBarCtrl rebars(rebar);

        PSTADE_PRECONDITION (
            (0 <= index)
            (pstade::copy_construct<UINT>(index) < rebars.GetBandCount())
        )

        REBARBANDINFO info; {
            info|gravy::size_initialized;
            info.fMask = RBBIM_ID;
            PSTADE_REQUIRE(rebars.GetBandInfo(index, &info));
        }

        return info.wID;
    }


} } // namespace pstade::tomato


#endif
