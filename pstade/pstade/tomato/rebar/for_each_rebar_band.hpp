#ifndef PSTADE_TOMATO_REBAR_FOR_EACH_REBAR_BAND_HPP
#define PSTADE_TOMATO_REBAR_FOR_EACH_REBAR_BAND_HPP


// PStade.Tomato
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/apple/sdk/windows.hpp>
#include <pstade/apple/wtl/ctrls.hpp> // CReBarCtrl
#include "../window/window_ref.hpp"
#include "./get_rebar_band_id.hpp"


namespace pstade { namespace tomato {


template< class Functor >
Functor for_each_rebar_band(window_ref rebar, Functor fun)
{
    WTL::CReBarCtrl rebars(rebar);

    for (int i = 0, count = rebars.GetBandCount(); i < count; ++i)
        fun(hWndReBar, tomato::get_rebar_band_id(rebar, i));

    return fun;
}


} } // namespace pstade::tomato


#endif
