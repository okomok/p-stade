#ifndef PSTADE_TOMATO_REBAR_GET_REBAR_BAND_INFO_HPP
#define PSTADE_TOMATO_REBAR_GET_REBAR_BAND_INFO_HPP


// PStade.Tomato
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// See:
//
// CFrameWindowImpl<>::AddSimpleReBarBandCtrl of WTL7.5


// Design:
//
// Any window can pretend to be a toolbar :-)


#include <boost/assert.hpp>
#include <pstade/apple/sdk/windows.hpp>
#include <pstade/require.hpp>
#include "../diet/valid.hpp"


namespace pstade { namespace tomato {


namespace get_rebar_band_info_detail {


    inline
    int get_button_count(HWND hWnd)
    {
        return static_cast<int>(::SendMessage(hWnd, TB_BUTTONCOUNT, 0, 0L));
    }


    inline
    bool get_first_item_rect(HWND hWnd, RECT& rc)
    {
        int nBtnCount = get_rebar_band_info_detail::get_button_count(hWnd);
        if (nBtnCount > 0) {
            PSTADE_REQUIRE(::SendMessage(hWnd, TB_GETITEMRECT, 0, reinterpret_cast<LPARAM>(&rc)));
            return true;
        }

        return false;
    }


    inline
    bool get_last_item_rect(HWND hWnd, RECT& rc)
    {
        int nBtnCount = get_rebar_band_info_detail::get_button_count(hWnd);
        if (nBtnCount > 0) {
            PSTADE_REQUIRE(::SendMessage(hWnd, TB_GETITEMRECT, nBtnCount-1, reinterpret_cast<LPARAM>(&rc)));
            return true;
        }

        return false;
    }


} // namespace get_rebar_band_info_detail


inline
UINT get_rebar_band_info_cxMinChild(HWND hWnd, bool hasTitle)
{
    BOOST_ASSERT(diet::valid(hWnd));
    
    if (hasTitle)
        return 0;

    RECT rc;
    if (get_rebar_band_info_detail::get_first_item_rect(hWnd, rc))
        return rc.right;

    return 0;
}


inline
UINT get_rebar_band_info_cyMinChild(HWND hWnd)
{
    BOOST_ASSERT(diet::valid(hWnd));
    
    RECT rc;
    if (get_rebar_band_info_detail::get_first_item_rect(hWnd, rc))
        return rc.bottom - rc.top;

    return 16;
}


inline
UINT get_rebar_band_info_cxIdeal(HWND hWnd)
{
    BOOST_ASSERT(diet::valid(hWnd));
    
    RECT rc;
    if (get_rebar_band_info_detail::get_last_item_rect(hWnd, rc))
        return rc.right;

    return 0;
}


} } // namespace pstade::tomato


#endif
