#ifndef PSTADE_TOMATO_REBAR_BAND_HPP
#define PSTADE_TOMATO_REBAR_BAND_HPP


// PStade.Tomato
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/assert.hpp>
#include <pstade/candy/add.hpp>
#include <pstade/candy/remove.hpp>
#include <pstade/gravy/sdk/windows.hpp>
#include <pstade/gravy/size_initialize.hpp>
#include <pstade/gravy/window_ptr.hpp>
#include <pstade/gravy/window_ref.hpp>
#include <pstade/require.hpp>
#include "./wtl/ctrls.hpp" // CReBarCtrl


namespace pstade { namespace tomato {


    struct rebar_band
    {
        rebar_band(gravy::window_ref rebar, UINT id) :
            m_rebar(rebar), m_id(id),
            m_index(m_rebar.IdToIndex(id))
        {
            BOOST_ASSERT("band id is valid." && m_index != -1);
        }

        gravy::window_ref rebar() const
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

        gravy::window_ptr child() const
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
            info|gravy::size_initialized;
            info.fMask = mask;
            PSTADE_REQUIRE(m_rebar.GetBandInfo(m_index, &info));
        }
    };


} } // namespace pstade::tomato


#endif
