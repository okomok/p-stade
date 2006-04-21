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
#include <boost/microsoft/sdk/tchar.hpp>
#include <boost/microsoft/sdk/windows.hpp>
#include <boost/mpl/int.hpp>
#include <boost/range/begin.hpp>
#include <boost/range/size.hpp>
#include <pstade/integral_cast.hpp>
#include <pstade/oven/equal.hpp>
#include <pstade/oven/null_terminate_range.hpp>
#include <pstade/require.hpp>
#include "../diet/valid.hpp"


namespace pstade { namespace tomato {


inline
void set_window_text(HWND hWnd, const TCHAR *pszNew)
{
    BOOST_ASSERT(diet::valid(hWnd));
    BOOST_ASSERT(diet::valid(pszNew));

    oven::null_terminate_range<const TCHAR *> strNew(pszNew);
    int newLen = pstade::integral(boost::size(strNew));

    typedef boost::mpl::int_<255> bufLen;
    boost::array<TCHAR, 1 + bufLen::value> bufOld;

    // fast check to see if text really changes (reduces flash in controls)
    if (newLen > bufLen::value ||
        ::GetWindowText(hWnd, boost::begin(bufOld), bufOld.static_size) != newLen ||
        !oven::equals(bufOld|oven::null_terminated, strNew))
    {
        PSTADE_REQUIRE(::SetWindowText(hWnd, pszNew));
    }
}


} } // namespace pstade::tomato


#endif
