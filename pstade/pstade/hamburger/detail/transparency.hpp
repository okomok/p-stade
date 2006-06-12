#ifndef PSTADE_HAMBURGER_DETAIL_TRANSPARENCY_HPP
#define PSTADE_HAMBURGER_DETAIL_TRANSPARENCY_HPP


#if !(_WIN32_WINNT >= 0x0500)
    #error requires '_WIN32_WINNT >= 0x0500'.
#endif


// PStade.Hamburger
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// See:
//
// http://www.codeproject.com/dialog/smoothalpha.asp


#include <boost/assert.hpp>
#include <pstade/apple/atl/win.hpp> // CWindow
#include <pstade/apple/sdk/windows.hpp>
#include <pstade/require.hpp>
#include <pstade/tomato/diet/valid.hpp>
#include <pstade/tomato/rgb.hpp>
#include "./view_attributes.hpp"


namespace pstade { namespace hamburger { namespace detail {


namespace transparency_detail {


    inline
    void add(HWND hWnd, COLORREF clr)
    {
        BOOST_ASSERT(diet::valid(hWnd));

        ATL::CWindow wnd(hWnd);
        wnd.ModifyStyleEx(0, WS_EX_LAYERED);
        PSTADE_REQUIRE(::SetLayeredWindowAttributes(wnd, clr, 1, LWA_COLORKEY));
    }


    inline
    void remove(HWND hWnd)
    {
        BOOST_ASSERT(diet::valid(hWnd));

        ATL::CWindow wnd(hWnd);
        wnd.ModifyStyleEx(WS_EX_LAYERED, 0);
    }


} // namespace transparency_detail


template< class Element >
void reset_transparency(Element& elem)
{
    boost::optional<COLORREF> clr = tomato::rgb(elem%Name_transparencyColor);
    if (clr)
        transparency_detail::add(*elem.window(), *clr);
}


template< class Element >
void remove_transparency(Element& elem)
{
    transparency_detail::remove(*elem.window());
}


} } } // namespace pstade::hamburger::detail


#endif
