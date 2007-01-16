#ifndef PSTADE_TOMATO_REBAR_ADD_REBAR_BAND_HPP
#define PSTADE_TOMATO_REBAR_ADD_REBAR_BAND_HPP


// PStade.Tomato
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <vector>
#include <boost/assert.hpp>
#include <boost/range/empty.hpp>
#include <pstade/apple/sdk/tchar.hpp>
#include <pstade/apple/sdk/windows.hpp>
#include <pstade/apple/wtl/ctrls.hpp> // CReBarCtrl
#include <pstade/candy/set.hpp>
#include <pstade/oven/appended.hpp>
#include <pstade/oven/as_c_str.hpp>
#include <pstade/oven/begin_end.hpp>
#include <pstade/oven/copy_range.hpp>
#include <pstade/oven/null_terminated.hpp>
#include <pstade/oven/pointed.hpp>
#include <pstade/require.hpp>
#include "../c_str.hpp"
#include "../size_initialize.hpp"
#include "../window/window_ref.hpp"
#include "./get_rebar_band_info.hpp"


namespace pstade { namespace tomato {


template< class CStringizable > // 'cx' can be 0.
void add_rebar_band(window_ref rebar, window_ref child, UINT fStyle, CStringizable const& str, UINT cx)
{
    BOOST_ASSERT("child window id must be valid." && ::GetDlgCtrlID(child) != 0);


    // info.lpText is not 'const'. 'const_cast' is dangerous,
    // so that, copy it.
    std::vector<TCHAR> text; {
        text = str|to_c_str|oven::as_c_str
            |oven::appended(_T('\0'))|oven::copied;
        BOOST_ASSERT(oven::is_null_terminated(text));
    }

    bool hasTitle = !boost::empty(text|oven::null_terminated);


    REBARBANDINFO info; {
        info|size_initialized;

#if (_WIN32_IE >= 0x0400)
        info.fMask = RBBIM_CHILD | RBBIM_CHILDSIZE | RBBIM_STYLE | RBBIM_ID | RBBIM_SIZE | RBBIM_IDEALSIZE;
#else
        info.fMask = RBBIM_CHILD | RBBIM_CHILDSIZE | RBBIM_STYLE | RBBIM_ID | RBBIM_SIZE;
#endif
        
        if (hasTitle)
            candy::set(info.fMask, RBBIM_TEXT);
        
        info.fStyle = fStyle;
        info.lpText = text|oven::pointed|oven::begins;
        info.hwndChild = child;
        info.wID = ::GetDlgCtrlID(child); // how's that

        info.cxMinChild = tomato::get_rebar_band_info_cxMinChild(child, hasTitle);
        info.cyMinChild = tomato::get_rebar_band_info_cyMinChild(child);
        
        // cx is the "current" width.
        if (cx == 0)
            info.cx = tomato::get_rebar_band_info_cxIdeal(child);
        else
            info.cx = cx;

#if (_WIN32_IE >= 0x0400)
        // Note: cxIdeal is used for CHEVRON. If MDI, cxIdeal is changed dynamically.
        info.cxIdeal = tomato::get_rebar_band_info_cxIdeal(child); // info.cx is not good.
#endif
    } // info


    PSTADE_REQUIRE(WTL::CReBarCtrl(rebar).InsertBand(-1, &info));


/* should be?
#if (_WIN32_IE >= 0x0501)
        DWORD dwExStyle = (DWORD)::SendMessage(child, TB_GETEXTENDEDSTYLE, 0, 0L);
        ::SendMessage(child, TB_SETEXTENDEDSTYLE, 0, dwExStyle | TBSTYLE_EX_HIDECLIPPEDBUTTONS);
#endif // (_WIN32_IE >= 0x0501)
*/

}


} } // namespace pstade::tomato


#endif
