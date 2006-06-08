#ifndef PSTADE_PIZZA_GET_WRITE_STATUSBAR_HPP
#define PSTADE_PIZZA_GET_WRITE_STATUSBAR_HPP


// PStade.Pizza
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/assert.hpp>
#include <pstade/apple/sdk/tchar.hpp>
#include <pstade/apple/sdk/windows.hpp>
#include <pstade/tomato/diet/valid.hpp>
#include "../error.hpp"
#include "../integer.hpp"
#include "../set_integer.hpp"


namespace pstade { namespace pizza {


template< class Profile > inline
void write_statusbar(Profile& pr, HWND hWndStatusBar)
{
    BOOST_ASSERT(diet::valid(hWndStatusBar));

    pizza::set_integer(pr, _T("statusbar.visible"), ::IsWindowVisible(hWndStatusBar) ? 1 : 0);
}


template< class Profile >
bool get_statusbar(Profile& pr, HWND hWndStatusBar)
{
    BOOST_ASSERT(diet::valid(hWndStatusBar));

    try {
        int val = pizza::integer(pr, _T("statusbar.visible"));
        ::ShowWindow(hWndStatusBar, val == 1 ? SW_SHOWNOACTIVATE : SW_HIDE);
    }
    catch (error&) {
        return false;
    }

    return true;
}


} } // namespace pstade::pizza


#endif
