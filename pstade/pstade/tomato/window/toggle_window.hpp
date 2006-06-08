#ifndef PSTADE_TOMATO_WINDOW_TOGGLE_WINDOW_HPP
#define PSTADE_TOMATO_WINDOW_TOGGLE_WINDOW_HPP


// PStade.Tomato
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/assert.hpp>
#include <pstade/apple/sdk/windows.hpp>
#include "../boolean_cast.hpp"
#include "../diet/valid.hpp"


namespace pstade { namespace tomato {


inline
bool toggle_window(HWND hWnd)
{
    BOOST_ASSERT(diet::valid(hWnd));

    BOOL bVisible = !::IsWindowVisible(hWnd);
    ::ShowWindow(hWnd, bVisible ? SW_SHOWNOACTIVATE : SW_HIDE);

    return tomato::boolean(bVisible);
}


} } // namespace pstade::tomato


#endif
