#ifndef PSTADE_TOMATO_REBAR_REBAR_BAND_GENERATOR_HPP
#define PSTADE_TOMATO_REBAR_REBAR_BAND_GENERATOR_HPP


// PStade.Tomato
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/apple/wtl/ctrls.hpp> // CReBarCtrl
#include "../window/window_ref.hpp"
#include "./get_rebar_band_id.hpp"
#include "./rebar_band.hpp"


namespace pstade { namespace tomato {


struct rebar_band_generator
{
    explicit rebar_band_generator(window_ref rebar) :
        m_rebar(rebar)
    { }

    typedef rebar_band yielded_type;

    template< class Yield >
    void operator()(Yield yield) const
    {
        for (int i = 0, count = m_rebar.GetBandCount(); i < count; ++i)
            yield( rebar_band(hWndReBar, tomato::get_rebar_band_id(m_rebar, i)) );
    }

    window_ref rebar() const
    {
        return m_rebar.m_hWnd;
    }

private:
    mutable WTL::CReBarCtrl m_rebar;
};


} } // namespace pstade::tomato


#endif
