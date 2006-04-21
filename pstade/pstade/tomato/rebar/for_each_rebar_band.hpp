#ifndef PSTADE_TOMATO_REBAR_FOR_EACH_REBAR_BAND_HPP
#define PSTADE_TOMATO_REBAR_FOR_EACH_REBAR_BAND_HPP


// PStade.Tomato
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/assert.hpp>
#include <boost/microsoft/sdk/windows.hpp>
#include <boost/microsoft/wtl/ctrls.hpp> // CReBarCtrl
#include "../diet/valid.hpp"
#include "./get_rebar_band_id.hpp"


namespace pstade { namespace tomato {


template< class Functor > inline
Functor for_each_rebar_band(HWND hWndReBar, Functor fun)
{
    BOOST_ASSERT(diet::valid(hWndReBar));

    WTL::CReBarCtrl rebar(hWndReBar);
    for (int i = 0, count = rebar.GetBandCount(); i < count; ++i)
        fun(hWndReBar, tomato::get_rebar_band_id(hWndReBar, i));

    return fun;
}


} } // namespace pstade::tomato


#endif
