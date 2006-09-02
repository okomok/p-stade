#ifndef PSTADE_TOMATO_REBAR_REBAR_BAND_HPP
#define PSTADE_TOMATO_REBAR_REBAR_BAND_HPP


// PStade.Tomato
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/assert.hpp>
#include <pstade/apple/sdk/windows.hpp>
#include <pstade/apple/wtl/ctrls.hpp> // CReBarCtrl
#include <pstade/candy/add.hpp>
#include <pstade/candy/remove.hpp>
#include <pstade/require.hpp>
#include "../size_initialize.hpp"
#include "../window/window_ref.hpp"


namespace pstade { namespace tomato {


struct rebar_band
{
    rebar_band(window_ref rebar, UINT id) :
        m_rebar(rebar), m_id(id),
        m_index(m_rebar.IdToIndex(id))
    {
        BOOST_ASSERT("band id is valid." && m_index != -1);
    }

    window_ref rebar() const
    {
        return m_rebar.m_hWnd;
    }

    UINT id() const
    {
        return m_id;
    }

    int index() const
    {
        return m_index;
    }

    window_ptr child() const
    {
        REBARBANDINFO info;
        info.hwndChild = NULL; // for ambiguous document.
        get_info(info, RBBIM_CHILD);
        return info.hwndChild;
    }

    bool is_visible() const
    {
        REBARBANDINFO info;
        get_info(info, RBBIM_STYLE);
        return !candy::test(info.fStyle, RBBS_HIDDEN);
    }

    void show(bool visible) const
    {
        PSTADE_REQUIRE(m_rebar.ShowBand(m_index, visible));
    }

    void modify_style(UINT rem, UINT add) const
    {
        REBARBANDINFO info;
        get_info(info, RBBIM_STYLE);
        candy::remove(info.fStyle, rem);
        candy::add(info.fStyle, add);
        PSTADE_REQUIRE(m_rebar.SetBandInfo(m_index, &info));
    }

private:
    mutable WTL::CReBarCtrl m_rebar;
    UINT m_id;
    int m_index;

    void get_info(REBARBANDINFO& info, UINT mask) const
    {
        info|size_initialized;
        info.fMask = mask;
        PSTADE_REQUIRE(m_rebar.GetBandInfo(m_index, &info));
    }
};


} } // namespace pstade::tomato


#endif
