#ifndef PSTADE_TOMATO_REBAR_TOGGLE_REBAR_BAND_HPP
#define PSTADE_TOMATO_REBAR_TOGGLE_REBAR_BAND_HPP


// PStade.Tomato
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include "./rebar_band.hpp"


namespace pstade { namespace tomato {


inline
bool toggle_rebar_band(rebar_band const& band)
{
    bool next = !band.is_visible();
    band.show(next);
    return next;
}


} } // namespace pstade::tomato


#endif
