#ifndef PSTADE_TOMATO_REBAR_TOGGLE_REBAR_BAND_HPP
#define PSTADE_TOMATO_REBAR_TOGGLE_REBAR_BAND_HPP


// PStade.Tomato
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/assert.hpp>
#include <boost/microsoft/sdk/windows.hpp>
#include "../diet/valid.hpp"
#include "./is_rebar_band_visible.hpp"
#include "./show_rebar_band.hpp"


namespace pstade { namespace tomato {


inline
bool toggle_rebar_band(HWND hWndReBar, UINT uBandID)
{
    BOOST_ASSERT(diet::valid(hWndReBar));

    bool new_vis = !tomato::is_rebar_band_visible(hWndReBar, uBandID);
    tomato::show_rebar_band(hWndReBar, uBandID, new_vis);
    return new_vis;
}


} } // namespace pstade::tomato


#endif
