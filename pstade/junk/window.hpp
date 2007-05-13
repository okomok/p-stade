#ifndef PSTADE_TOMATO_WINDOW_WINDOW_HPP
#define PSTADE_TOMATO_WINDOW_WINDOW_HPP


// PStade.Tomato
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// What:
//
// 'ATL::CWindow' is nullable, fix it.


#include <boost/assert.hpp>
#include <pstade/apple/atl/win.hpp> // CWindow
#include <pstade/apple/sdk/windows.hpp> // HWND


namespace pstade { namespace tomato {


struct window :
    ATL::CWindow
{
    explicit window(HWND hWnd) :
        ATL::CWindow(hWnd)
    {
        BOOST_ASSERT(::IsWindow(hWnd));
    }

    HWND operator *() const
    {
        BOOST_ASSERT(::IsWindow(hWnd));
        return m_hWnd;
    }

    operator HWND() const; // hide base's.
};


} } // namespace pstade::tomato


#endif
