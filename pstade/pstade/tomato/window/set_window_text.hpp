#ifndef PSTADE_TOMATO_WINDOW_SET_WINDOW_TEXT_HPP
#define PSTADE_TOMATO_WINDOW_SET_WINDOW_TEXT_HPP


// PStade.Tomato
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// Port of:
//
// MFC7::AfxSetWindowText


#include <boost/array.hpp>
#include <boost/range/begin.hpp>
#include <pstade/apple/sdk/tchar.hpp>
#include <pstade/apple/sdk/windows.hpp>
#include <pstade/oven/distance.hpp>
#include <pstade/oven/equals.hpp>
#include <pstade/oven/null_terminate_range.hpp>
#include <pstade/require.hpp>
#include <pstade/static_c.hpp>
#include "../c_str.hpp"
#include "./window_ref.hpp"


namespace pstade { namespace tomato {


template< class CStringizable >
void set_window_text(window_ref wnd, CStringizable const& str)
{
    TCHAR const *pszNew = str|c_stringized;
    oven::null_terminate_range<TCHAR const *> strNew(pszNew);
    int newLen = static_cast<int>(oven::distance(strNew));

    typedef static_c<int, 255> bufLen;
    boost::array<TCHAR, 1 + bufLen::value> bufOld;

    // fast check to see if text really changes (reduces flash in controls)
    if (newLen > bufLen::value ||
        ::GetWindowText(wnd, boost::begin(bufOld), bufOld.static_size) != newLen ||
        !oven::equals(bufOld|oven::null_terminated, strNew))
    {
        PSTADE_REQUIRE(::SetWindowText(wnd, pszNew));
    }
}


} } // namespace pstade::tomato


#endif
