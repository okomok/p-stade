#ifndef PSTADE_PIZZA_GET_WRITE_WINDOW_PLACEMENT_HPP
#define PSTADE_PIZZA_GET_WRITE_WINDOW_PLACEMENT_HPP


// PStade.Pizza
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#if !defined(_WIN32_WCE)


#include <pstade/apple/sdk/tchar.hpp>
#include <pstade/apple/sdk/windows.hpp>
#include <pstade/tomato/size_initialize.hpp>
#include "../integer.hpp"
#include "../set_integer.hpp"


namespace pstade { namespace pizza {


template< class Profile >
void write_window_placement(Profile& pr, const WINDOWPLACEMENT& wndpl)
{
    pizza::set_integer(pr, _T("placement.flags"),                   wndpl.flags);
    pizza::set_integer(pr, _T("placement.showCmd"),                 wndpl.showCmd);
    pizza::set_integer(pr, _T("placement.ptMinPosition.x"),         wndpl.ptMinPosition.x);
    pizza::set_integer(pr, _T("placement.ptMinPosition.y"),         wndpl.ptMinPosition.y);
    pizza::set_integer(pr, _T("placement.ptMaxPosition.x"),         wndpl.ptMaxPosition.x);
    pizza::set_integer(pr, _T("placement.ptMaxPosition.y"),         wndpl.ptMaxPosition.y);
    pizza::set_integer(pr, _T("placement.rcNormalPosition.left"),   wndpl.rcNormalPosition.left);
    pizza::set_integer(pr, _T("placement.rcNormalPosition.top"),    wndpl.rcNormalPosition.top);
    pizza::set_integer(pr, _T("placement.rcNormalPosition.right"),  wndpl.rcNormalPosition.right);
    pizza::set_integer(pr, _T("placement.rcNormalPosition.bottom"), wndpl.rcNormalPosition.bottom);
}


template< class Profile >
WINDOWPLACEMENT get_window_placement(Profile& pr)
{
    WINDOWPLACEMENT wndpl;

    wndpl|tomato::size_initialized;
    wndpl.flags =                   pizza::integer(pr, _T("placement.flags"));
    wndpl.showCmd =                 pizza::integer(pr, _T("placement.showCmd"));
    wndpl.ptMinPosition.x =         pizza::integer(pr, _T("placement.ptMinPosition.x"));
    wndpl.ptMinPosition.y =         pizza::integer(pr, _T("placement.ptMinPosition.y"));
    wndpl.ptMaxPosition.x =         pizza::integer(pr, _T("placement.ptMaxPosition.x"));
    wndpl.ptMaxPosition.y =         pizza::integer(pr, _T("placement.ptMaxPosition.y"));
    wndpl.rcNormalPosition.left =   pizza::integer(pr, _T("placement.rcNormalPosition.left"));
    wndpl.rcNormalPosition.top =    pizza::integer(pr, _T("placement.rcNormalPosition.top"));
    wndpl.rcNormalPosition.right =  pizza::integer(pr, _T("placement.rcNormalPosition.right"));
    wndpl.rcNormalPosition.bottom = pizza::integer(pr, _T("placement.rcNormalPosition.bottom"));

    return wndpl;
}


} } // namespace pstade::pizza


#endif // !defined(_WIN32_WCE)


#endif
