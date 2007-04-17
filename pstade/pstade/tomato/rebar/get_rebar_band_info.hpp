#ifndef PSTADE_TOMATO_REBAR_GET_REBAR_BAND_INFO_HPP
#define PSTADE_TOMATO_REBAR_GET_REBAR_BAND_INFO_HPP


// PStade.Tomato
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// See:
//
// CFrameWindowImpl<>::AddSimpleReBarBandCtrl of WTL7.5


// Design:
//
// Any window can pretend to be a toolbar :-)


#include <pstade/apple/sdk/windows.hpp>
#include <pstade/copy_construct.hpp>
#include <pstade/require.hpp>
#include "../window/window_ref.hpp"


namespace pstade { namespace tomato {


namespace get_rebar_band_info_detail {


    inline
    int get_button_count(window_ref wnd)
    {
        return pstade::copy_construct<int>(::SendMessage(wnd, TB_BUTTONCOUNT, 0, 0L));
    }


    inline
    bool get_first_item_rect(window_ref wnd, RECT& rc)
    {
        int nBtnCount = get_rebar_band_info_detail::get_button_count(wnd);
        if (nBtnCount > 0) {
            PSTADE_REQUIRE(::SendMessage(wnd, TB_GETITEMRECT, 0, reinterpret_cast<LPARAM>(&rc)));
            return true;
        }

        return false;
    }


    inline
    bool get_last_item_rect(window_ref wnd, RECT& rc)
    {
        int nBtnCount = get_rebar_band_info_detail::get_button_count(wnd);
        if (nBtnCount > 0) {
            PSTADE_REQUIRE(::SendMessage(wnd, TB_GETITEMRECT, nBtnCount-1, reinterpret_cast<LPARAM>(&rc)));
            return true;
        }

        return false;
    }


} // namespace get_rebar_band_info_detail


inline
UINT get_rebar_band_info_cxMinChild(window_ref wnd, bool hasTitle)
{    
    if (hasTitle)
        return 0;

    RECT rc;
    if (get_rebar_band_info_detail::get_first_item_rect(wnd, rc))
        return rc.right;

    return 0;
}


inline
UINT get_rebar_band_info_cyMinChild(window_ref wnd)
{    
    RECT rc;
    if (get_rebar_band_info_detail::get_first_item_rect(wnd, rc))
        return rc.bottom - rc.top;

    return 16;
}


inline
UINT get_rebar_band_info_cxIdeal(window_ref wnd)
{
    RECT rc;
    if (get_rebar_band_info_detail::get_last_item_rect(wnd, rc))
        return rc.right;

    return 0;
}


} } // namespace pstade::tomato


#endif
